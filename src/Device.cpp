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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string.h>

#include "Device.h"

Device::Device(std::string* usbtmc_handler) throw (std::string) {
    if ((usbtmc = open(usbtmc_handler->c_str(), O_RDWR)) < 0) {
        std::stringstream ss;
        ss << "open: " << strerror(errno) << std::endl;
        ss << "Device was not found at " << *usbtmc_handler << std::endl;
        throw (ss.str());
    }
}

Device::~Device() {
    if (usbtmc > 0) {
        close(usbtmc);
    }
}

void Device::command(std::string comm) {
    if ((write(usbtmc, comm.c_str(), comm.length())) < 0) {
        perror("write");
        exit(1);
    }
    
}

std::string Device::query(std::string comm, std::string &errstring) {
    this->command(comm);

    uint8_t* buf = NULL;
    int read_errno = 0;
    int bufSize = _read_from_device(buf, read_errno);

    if (read_errno) {
        std::stringstream ss;
        ss << "Error reading from device: " << strerror(read_errno) << std::endl;
        ss << "Incorrect command or command without output? For commands without output use -c option." << std::endl;
        errstring.assign(ss.str());
    }
    
    std::string ret;
    ret.assign((char*) buf, bufSize);

    free(buf);

    return ret;
}

int Device::_read_from_device(uint8_t* &buf, int &read_errno) {
    int bufAllocSize = CHUNKSIZE;

    buf = (uint8_t*) malloc(bufAllocSize);

    int bufpos = 0;
    int bsize;

    while ((bsize = read(usbtmc, buf + bufpos, CHUNKSIZE)) > 0) {
        bufpos = bufpos + bsize;
        if (bsize != CHUNKSIZE) {
            break;
        }
        if (bufpos + CHUNKSIZE > bufAllocSize) {
            bufAllocSize = bufAllocSize * 2;
            buf = (uint8_t*) realloc(buf, bufAllocSize);
        }
    }

    if (bsize < 0) {
        read_errno = errno;
    }

    return bufpos;
}

std::vector<uint8_t> Device::waveform(std::string comm) {
    this->command(comm);

    uint8_t* buf = NULL;
    int read_errno = 0;
    int bufSize = _read_from_device(buf, read_errno);

    std::vector<uint8_t> ret;
    ret.assign(buf, buf + bufSize);

    free(buf);

    return ret;
}
