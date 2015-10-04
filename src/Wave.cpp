/****************************************************************************
**                                                                         **
**  This file is part of SiglScope.                                        **
**  SiglScope is set of graphical and command line programs for            **
**  interacting with Siglent SDS 1000 series Digital Storage Oscilloscope. **
**                                                                         **
**  This program is free software: you can redistribute it and/or modify   **
**  it under the terms of the GNU General Public License as published by   **
**  the Free Software Foundation, either version 3 of the License, or      **
**  (at your option) any later version.                                    **
**                                                                         **
**  This program is distributed in the hope that it will be useful,        **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of         **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          **
**  GNU General Public License for more details.                           **
**                                                                         **
**  You should have received a copy of the GNU General Public License      **
**  along with this program.  If not, see http://www.gnu.org/licenses/.    **
**                                                                         **
************************************************************************** **
**           Author: Markko Merzin                                         **
**          Contact: markko.merzin@gmail.com                               **
**             Date: 30.09.2015                                            **
**          Version: 0.1                                                   **
****************************************************************************/


#include "Wave.h"
#include "template_siglent_dso_sds1000.h"
#include <sstream>
#include <math.h>
// #include <complex>
#include <fftw3.h>

Wave::Wave() {
    this->wave = NULL;
    this->spectrum = NULL;
}

// Wave::Wave(const Wave& orig) {
//}

Wave::~Wave() {
    if (this->wave != NULL) {
        wave->clear();
        delete wave;
    }
    
    if (this->spectrum != NULL) {
        spectrum->clear();
        delete spectrum;
    }
}

int Wave::loadWave_Siglent_DSO_1000(std::vector<uint8_t> raw_wave_input) {
    if (raw_wave_input.size() < 8) {
        return 1;
    }
    
    siglentdso1000_wf_header_t* fullheader = NULL;

    const char* knownstring = "WAVEDESC";
    unsigned int offset;
    int wave_found = 0;    
    for (offset = 0; offset < (raw_wave_input.size() - 8); offset++) { // i'll boyer-moore when i grow up!
        if (memcmp(&(raw_wave_input[offset]), knownstring, 8) == 0) {
            fullheader = (siglentdso1000_wf_header_t*) &(raw_wave_input[offset]);
            wave_found = 1;
            break;
        }
    }

    if (wave_found == 0) {
        return 1;
    }

    int wave_offset = fullheader->WAVE_DESCRIPTOR;

    // Seems like bug in DSO firmware. WAVE_ARRAY_1 field is not updated when long memory is in use
    int wave_len;
    if (raw_wave_input.size() > (1024 * 1024)) {
        wave_len = 1024 * 1024 - 1024; // another bug in DSO? last kb is always garbage in long memory mode.
    } else if (raw_wave_input.size() > (512 * 1024)) {
        wave_len = 512 * 1024 - 1024;
    } else {
        wave_len = fullheader->WAVE_ARRAY_1;
    }

    float vertical_gain = fullheader->VERTICAL_GAIN;
    float vertical_offset = fullheader->VERTICAL_OFFSET;

    double horizontal_offset = fullheader->HORIZ_OFFSET;
    float horizontal_interval = fullheader->HORIZ_INTERVAL;

    int8_t* wavedata = (int8_t*) &(raw_wave_input[offset + wave_offset]);

    if (this->wave == NULL) {
        this->wave = new std::vector<std::pair<double, double>>;
    } else {
        this->wave->clear();
    }

    for (int c = 0; c < wave_len; c++) {
        float datapoint = vertical_gain * wavedata[c] - vertical_offset;
        float timepoint = horizontal_offset + c * horizontal_interval;
        std::pair<double, double> pair;
        pair.DATAPOINT = datapoint;
        pair.TIMEPOINT = timepoint;
        wave->push_back(pair);
    }

    return 0;
}

std::vector<std::pair<double, double>>*Wave::getWave() {
    return this->wave;
}

std::vector<std::pair<double, double>>*Wave::getSpectrum() {
    return this->spectrum;
}


std::string Wave::getWaveCSV() {
    std::stringstream ss;

    ss << "t(s);U(V)" << std::endl;

    for (unsigned int c = 0; c < this->wave->size(); c++) {
        ss << this->wave->at(c).TIMEPOINT << ";" << this->wave->at(c).DATAPOINT << std::endl;
    }

    return ss.str();
}


void Wave::calculateSpectrum() {

#define WAVE_WINDOW_FRACTION 10

    if (this->spectrum == NULL) {
        this->spectrum = new std::vector<std::pair<double,double>>();
    } else {
        this->spectrum->clear();
    }



    int wave_len = this->wave->size();
    int window_len = this->wave->size() / WAVE_WINDOW_FRACTION;
    int window_step = window_len / 2;
    int windows_count = wave_len / window_step - 1;
    int output_size = window_len / 2 + 1;


    double averaged_results[output_size];
    bool firstpass = true;

    double sample_fulltime = (this->wave->back().TIMEPOINT - this->wave->front().TIMEPOINT) / WAVE_WINDOW_FRACTION;
    double nyquist_freq = (1 / (sample_fulltime / window_len)) / 2;
    double freq_granule = nyquist_freq / output_size;

    double window[window_len];
    for(int i = 0; i < window_len; i++) {
        window[i] = 0.54 - (0.46 * cos( 2 * M_PI * (i / ((window_len - 1) * 1.0))));
    }



    double* input_buffer = fftw_alloc_real(window_len);
    fftw_complex* output_buffer = fftw_alloc_complex(output_size);
    int flags = FFTW_ESTIMATE;
    fftw_plan plan = fftw_plan_dft_r2c_1d(window_len, input_buffer, output_buffer, flags);

    int window_pos = 0;
    while (window_pos < windows_count) {
        int prefix = window_pos * window_step;
        for (int c = 0; c < window_len; c++) {
            input_buffer[c] = wave->at(prefix + c).DATAPOINT * window[c];
        }

        fftw_execute(plan);

        for (int c = 0; c < output_size; c++) {

            double amplitude = 2 * sqrt(pow(output_buffer[c][0], 2) + pow(output_buffer[c][1], 2)) / window_len;

            if (firstpass) {
                averaged_results[c] = amplitude;
            } else {
                averaged_results[c] = averaged_results[c] + amplitude;
            }

        }
        firstpass = false;
        window_pos++;
    }

    for (int c = 0; c < output_size; c++) {
        double amplitude = 10 * log10(averaged_results[c] / windows_count);

        double freq = freq_granule * c;

        std::pair<double, double> pair;
        pair.DATAPOINT = amplitude;
        pair.FREQPOINT = freq;
        this->spectrum->push_back(pair);
    }


    fftw_free(input_buffer);
    fftw_free(output_buffer);
    fftw_destroy_plan(plan);


}

std::string Wave::getSpectrumCSV() {
    if (this->spectrum == NULL) {
        return std::string("NULL");
    }
    std::stringstream ss;

    ss << "Hz;dBV" << std::endl;

    for (unsigned int c = 0; c < this->spectrum->size(); c++) {
        ss << this->spectrum->at(c).FREQPOINT << ";" << this->spectrum->at(c).DATAPOINT << std::endl;
    }

    return ss.str();
    
}
