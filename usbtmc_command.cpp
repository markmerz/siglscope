/* 
 * File:   main.cpp
 * Author: markko
 *
 * Created on laupäev, 5. september 2015. a, 1:47
 */

#include <cstdlib>
#include <iostream>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include <math.h>
#include <fftw3.h>

#include "Device.h"
#include "Wave.h"
#include "template_siglent_dso_sds1000.h"
#include <getopt.h>
#include <sstream>

void complaint(int);

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    std::string* usbtmc_device = new std::string("/dev/usbtmc0");
    int quiet_command = 0;

    const struct option longopts[] = {
        {"version", no_argument, NULL, 'v'},
        {"help", no_argument, NULL, 'h'},
        {"device", required_argument, NULL, 'd'},
        {"command", no_argument, NULL, 'c'},
        {0, 0, 0, 0},
    };

    int index;
    int iarg = 0;

    //turn off getopt error message
    opterr = 1;

    while (iarg != -1) {
        iarg = getopt_long(argc, argv, "cd:vh", longopts, &index);

        switch (iarg) {

            case 'v':
                std::cout << "Version: 0.0" << std::endl;
                exit(0);
            case 'd':
                free(usbtmc_device);
                usbtmc_device = new std::string(optarg);
                break;
            case 'c':
                quiet_command = 1;
                break;
            case 'h':
                complaint(0);
                exit(0);
            case '?':
                complaint(1);
                exit(1);
        }
    }

    std::stringstream commandss;
    while (optind < argc) {
        commandss << argv[optind++] << " ";
    }
    std::string command = commandss.str();

    if (command.size() == 0) {
        complaint(1);
        exit(1);
    }

    Device* dev;
    try {
        dev = new Device(usbtmc_device);
    } catch (std::string ex) {
        std::cerr << ex << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (quiet_command) {
        dev->command(command);
    } else {
        std::string errstring;
        std::cout << dev->query(command, errstring);
        if (errstring.size() > 0) {
            std::cerr << errstring << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
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