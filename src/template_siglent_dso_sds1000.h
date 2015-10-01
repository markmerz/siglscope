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


#ifndef WAVEFORMHEADER_H
#define	WAVEFORMHEADER_H

enum COMM_TYPE_ENUM {
    byte = 0,
    word = 1
};

enum COMM_ORDER_ENUM {
    HIFIRST = 0,
    LOFIRST = 1
};

typedef struct __attribute__((__packed__)) {
    /*
    ;                 time_stamp        double precision floating point number,
    ;                                   for the number of seconds and some bytes
    ;                                   for minutes, hours, days, months and year.
    ;
    ;                                   double  seconds     (0 to 59)
    ;                                   byte    minutes     (0 to 59)
    ;                                   byte    hours       (0 to 23)
    ;                                   byte    days        (1 to 31)
    ;                                   byte    months      (1 to 12)
    ;                                   word    year        (0 to 16000)
    ;                                   word    unused
    ;                                   There are 16 bytes in a time field.
     */
    double seconds;
    int8_t minutes;
    int8_t hours;
    int8_t days;
    int8_t months;
    int16_t year;
    int16_t unused;
} time_stamp;

enum RECORD_TYPE_ENUM {
    single_sweep = 0,
    interleaved = 1,
    histogram = 2,
    graph = 3,
    filter_coefficient = 4,
    complex = 5,
    extrema = 6,
    sequence_obsolete = 7,
    centered_RIS = 8,
    peak_detect = 9

};

enum PROCESSING_DONE {
    no_processing = 0,
    fir_filter = 1,
    interpolated = 2,
    sparsed = 3,
    autoscaled = 4,
    no_result = 5,
    rolling = 5,
    cumulative = 7

};

enum TIMEBASE_ENUM {
    tb_1_ns_per_div = 0, //        _0       1_ns/div      
    tb_2p5_ns_per_div = 1, //        _1       2.5_ns/div     
    tb_5_ns_per_div = 2, //        _2       5_ns/div    
    tb_10_ns_per_div = 3, //        _3       10_ns/div     
    tb_25_ns_per_div = 4, //        _4       25_ns/div    
    tb_50_ns_per_div = 5, //        _5       50_ns/div  
    tb_100_ns_per_div = 6, //       _6       100_ns/div   
    tb_250_ns_per_div = 7, //       _7       250_ns/div   
    tb_500_ns_per_div = 8, //        _8       500_ns/div   
    tb_1_us_per_div = 9, //        _9       1_us/div  
    tb_2p5_us_per_div = 10, //        _10      2.5_us/div    
    tb_5_us_per_div = 11, //        _11      5_us/div     
    tb_10_us_per_div = 12, //       _12      10_us/div  
    tb_25_us_per_div = 13, //       _13      25_us/div      
    tb_50_us_per_div = 14, //       _14      50_us/div     
    tb_100_us_per_div = 15, //        _15      100_us/div   
    tb_250_us_per_div = 16, //       _16      250_us/div   
    tb_500_us_per_div = 17, //       _17      500_us/div      
    tb_1_ms_per_div = 18, //       _18      1_ms/div      
    tb_2p5_ms_per_div = 19, //       _19      2.5_ms/div      
    tb_5_ms_per_div = 20, //       _20      5_ms/div     
    tb_10_ms_per_div = 21, //       _21      10_ms/div   
    tb_25_ms_per_div = 22, //       _22      25_ms/div    
    tb_50_ms_per_div = 23, //      _23      50_ms/div      
    tb_100_ms_per_div = 24, //       _24      100_ms/div    
    tb_250_ms_per_div = 25, //       _25      250_ms/div    
    tb_500_ms_per_div = 26, //       _26      500_ms/div    
    tb_1_s_per_div = 27, //       _27      1_s/div    
    tb_2p5_s_per_div = 28, //       _28      2.5_s/div   
    tb_5_s_per_div = 29, //      _29      5_s/div    
    tb_10_s_per_div = 30, //      _30      10_s/div    
    tb_25_s_per_div = 31, //       _31      25_s/div  
    tb_50_s_per_div = 32, //       _32      50_s/div   
    tb_external = 100, //       _100     EXTERNAL  


};

enum VERT_COUPLING_ENUM {
    vc_DC_50_Ohms = 0, //    _0      DC_50_Ohms      
    vc_ground = 1, //    _1      ground           
    vc_DC_1MOhm = 2, //    _2      DC_1MOhm    
    vc_groud2 = 3, //    _3      ground           
    vc_AC_1MOhm = 4 //    _4      AC_1MOhm   

};

enum FIXED_VERT_GAIN_ENUM {
    fvg_2mV_p_div = 0, //   _0       2_mV/div     
    fvg_5mV_p_div = 1, //   _1       5_mV/div     
    fvg_10mV_p_div = 2, //   _2       10_mV/div   
    fvg_20mV_p_div = 3, //   _3       20_mV/div    
    fvg_50mV_p_div = 4, //   _4       50_mV/div   
    fvg_100mV_p_div = 5, //   _5       100_mV/div 
    fvg_200mV_p_div = 6, //   _6       200_mV/div  
    fvg_500mV_p_div = 7, //   _7       500_mV/div  
    fvg_1V_p_div = 8, //   _8       1_V/div  
    fvg_2V_p_div = 9, //   _9       2_V/div 
    fvg_5V_p_div = 10, //   _10      5_V/div      
    fvg_10V_p_div = 11, //   _11      10_V/div             
};

enum BANDWIDTH_LIMIT_ENUM {
    off = 0, // _0      off              
    on = 1 // _1      on                                         
};

enum WAVE_SOURCE_ENUM {
    channel_1 = 0, // _0      CHANNEL_1        
    channel_2 = 1, // _1      CHANNEL_2        
    channel_3 = 2, // _2      CHANNEL_3        
    channel_4 = 3, // _3      CHANNEL_4        
    channel_unknown = 9 //_9      UNKNOWN                                     
};

typedef struct __attribute__((__packed__)) {
    char DESCRIPTOR_NAME[16]; //the first 8 chars are always WAVEDESC
    char TEMPLATE_NAME[16];
    uint16_t COMM_TYPE; // see COMM_TYPE_ENUM; chosen by remote command COMM_FORMAT
    uint16_t COMM_ORDER; // see COMM_ORDER_ENUM
    
    int32_t WAVE_DESCRIPTOR; // length in bytes of block WAVEDESC
    int32_t USER_TEXT; // length in bytes of block USERTEXT
    int32_t RES_DESC1;

    int32_t TRIGTIME_ARRAY; // length in bytes of TRIGTIME array

    int32_t RIS_TIME_ARRAY; // length in bytes of RIS_TIME array 

    int32_t RES_ARRAY1; //an expansion entry is reserved 
    int32_t WAVE_ARRAY_1; //         ; length in bytes of 1st simple 
    //         ; data array. In transmitted waveform, 
    //         ; represent the number of transmitted 
    //         ; bytes in accordance with the NP 
    //         ; parameter of the WFSU remote command 
    //        ; and the used format (see COMM_TYPE). 

    int32_t WAVE_ARRAY_2; //       ; length in bytes of 2nd simple 
    //          ; data array 

    int32_t RES_ARRAY2; //          
    int32_t RES_ARRAY3; //         ; 2 expansion entries are reserved 

    // The following variables identify the instrument 
    char INSTRUMENT_NAME[16];
    int32_t INSTRUMENT_NUMBER;

    char TRACE_LABEL[16]; // identifies the waveform. 

    int16_t RESERVED1; //           
    int16_t RESERVED2; //          ; 2 expansion entries 

    // ; The following variables describe the waveform and the time at 
    // ; which the waveform was generated. 

    int32_t WAVE_ARRAY_COUNT; //   ; number of data points in the data 
    //   ; array. If there are two data 
    //   ; arrays (FFT or Extrema), this number 
    //   ; applies to each array separately. 

    int32_t PNTS_PER_SCREEN; //     ; nominal number of data points 
    //      ; on the screen 

    int32_t FIRST_VALID_PNT; // : long    ; count of number of points to skip 
    //      ; before first good point 
    //      ; FIRST_VALID_POINT = 0 
    //      ; for normal waveforms. 

    int32_t LAST_VALID_PNT; //: long     ; index of last good data point
    //       ; in record before padding (blanking)
    //       ; was started.
    //       ; LAST_VALID_POINT = WAVE_ARRAY_COUNT-1
    //       ; except for aborted sequence
    //       ; and rollmode acquisitions

    int32_t FIRST_POINT; //: long        ; for input and output, indicates
    //          ; the offset relative to the
    //          ; beginning of the trace buffer.
    //          ; Value is the same as the FP parameter
    //          ; of the WFSU remote command.

    int32_t SPARSING_FACTOR; // : long    ; for input and output, indicates
    //      ; the sparsing into the transmitted
    //      ; data block.
    //      ; Value is the same as the SP parameter
    //      ; of the WFSU remote command.

    int32_t SEGMENT_INDEX; //: long      ; for input and output, indicates the
    //        ; index of the transmitted segment.
    //        ; Value is the same as the SN parameter
    //        ; of the WFSU remote command.

    int32_t SUBARRAY_COUNT; //: long     ; for Sequence, acquired segment count,
    //       ; between 0 and NOM_SUBARRAY_COUNT

    int32_t SWEEPS_PER_ACQ; //: long     ; for Average or Extrema,
    //       ; number of sweeps accumulated
    //       ; else 1

    int16_t POINTS_PER_PAIR; //: word    ; for Peak Dectect waveforms (which always
    //      ; include data points in DATA_ARRAY_1 and
    //     ; min/max pairs in DATA_ARRAY_2).
    //      ; Value is the number of data points for
    //      ; each min/max pair.

    int16_t PAIR_OFFSET; //: word        ; for Peak Dectect waveforms only
    //          ; Value is the number of data points by
    //          ; which the first min/max pair in
    //          ; DATA_ARRAY_2 is offset relative to the
    //          ; first data value in DATA_ARRAY_1.

    float VERTICAL_GAIN; //: float     

    float VERTICAL_OFFSET; // : float   ; to get floating values from raw data :
    //        ; VERTICAL_GAIN * data - VERTICAL_OFFSET

    float MAX_VALUE; // : float         ; maximum allowed value. It corresponds
    //               ; to the upper edge of the grid.

    float MIN_VALUE; //: float         ; minimum allowed value. It corresponds
    //                ; to the lower edge of the grid.

    int16_t NOMINAL_BITS; //: word       ; a measure of the intrinsic precision
    //            ; of the observation: ADC data is 8 bit
    //            ;    averaged data is 10-12 bit, etc.

    int16_t NOM_SUBARRAY_COUNT; // : word ; for Sequence, nominal segment count
    //     ; else 1

    float HORIZ_INTERVAL; // : float    ; sampling interval for time domain
    //          ;  waveforms

    double HORIZ_OFFSET; // : double     ; trigger offset for the first sweep of
    //            ; the trigger, seconds between the
    //           ; trigger and the first data point

    double PIXEL_OFFSET; //: double     ; needed to know how to display the
    //           ; waveform

    char VERTUNIT[48]; // : unit_definition  ; units of the vertical axis

    char HORUNIT[48]; // : unit_definition   ; units of the horizontal axis

    float HORIZ_UNCERTAINTY; //: float ; uncertainty from one acquisition to the
    //      ; next, of the horizontal offset in seconds

    time_stamp TRIGGER_TIME; // : time_stamp ; time of the trigger

    float ACQ_DURATION; //: float      ; duration of the acquisition (in sec)
    //            ; in multi-trigger waveforms.
    //            ; (e.g. sequence, RIS,  or averaging)
    uint16_t RECORD_TYPE; // see RECORD_TYPE_ENUM

    uint16_t PROCESSING_DONE; // see PROCESSING_DONE_ENUM

    int16_t RESERVED5; // : word          ; expansion entry
    int16_t RIS_SWEEPS; //: word         ; for RIS, the number of sweeps
    //            ; else 1

    // ; The following variables describe the basic acquisition
    //; conditions used when the waveform was acquired
    uint16_t TIMEBASE; // see TIMEBASE_ENUM
    uint16_t VERT_COUPLING; // see VERT_COUPLING_ENUM

    float PROBE_ATT; // : float         
    uint16_t FIXED_VERT_GAIN; // see FIXED_VERT_GAIN_ENUM

    uint16_t BANDWIDTH_LIMIT; // see BANDWIDTH_LIMIT_ENUM

    float VERTICAL_VERNIER; //: float  

    float ACQ_VERT_OFFSET; //: float   

    uint16_t WAVE_SOURCE; // see WAVE_SOURCE_ENUM

} siglentdso1000_wf_header_t;

#endif	/* WAVEFORMHEADER_H */

