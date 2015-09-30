/* 
 * File:   accwave_siglentsds1000.c
 * Author: markko
 *
 * Created on pühapäev, 13. september 2015. a, 22:39
 */

#include <cstdlib>
#include "Device.h"
#include "Wave.h"
#include <vector>
#include <getopt.h>
#include <sstream>

void complaint(int);

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    std::string* usbtmc_device = new std::string("/dev/usbtmc0");
    std::string* dso_channel = new std::string("1");
    
    const struct option longopts[] = {
        {"version", no_argument, NULL, 'v'},
        {"help", no_argument, NULL, 'h'},
        {"device", required_argument, NULL, 'd'},
        {"channel", required_argument, NULL, 'c'},
        {0, 0, 0, 0},
    };

    int index;
    int iarg = 0;

    //turn on getopt error message
    opterr = 1;

    while (iarg != -1) {
        iarg = getopt_long(argc, argv, "c:d:vh", longopts, &index);

        switch (iarg) {

            case 'v':
                std::cout << "Version: 0.0" << std::endl;
                exit(0);
            case 'd':
                free(usbtmc_device);
                usbtmc_device = new std::string(optarg);
                break;
            case 'c':
                free(dso_channel);
                dso_channel = new std::string(optarg);
                break;
            case 'h':
                complaint(0);
                exit(0);
            case '?':
                complaint(1);
                exit(1);
        }
    }

    Device* dev;
    try {
        dev = new Device(usbtmc_device);
    } catch (std::string ex) {
        std::cerr << ex << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    std::string wavecommand = "C" + *dso_channel + ":WF? ALL";
    
    vector<uint8_t> raw_wave_input = dev->waveform(wavecommand);


    delete dev;

    Wave* wave = new Wave();

    if (wave->loadWave_Siglent_DSO_1000(raw_wave_input)) {
        cerr << "ERROR: Waveform data was not found from input." << endl;
        exit(EXIT_FAILURE);
    }

    std::cout << wave->getWaveCSV();
    
    return (EXIT_SUCCESS);
}

void complaint(int dest_err) {
    std::stringstream helptext;
    helptext << "Dog ate my helpfile!" << std::endl;

    if (dest_err) {
        std::cerr << helptext.str();
    } else {
        std::cout << helptext.str();
    }
}