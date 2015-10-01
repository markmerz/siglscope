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


#ifndef DEVICE_H
#define	DEVICE_H

#define CHUNKSIZE 1024

#include <string>
#include <vector>
#include <cstdint>

class Device {
public:
    Device(std::string* usbtmc_handler) throw(std::string);
    Device(const Device& orig);
    virtual ~Device();
    
    void command(std::string comm);
    std::string query(std::string comm, std::string &errstring);
    
    std::vector<uint8_t> waveform(std::string comm);
    
private:
    int usbtmc;
    
    int _read_from_device(uint8_t* &buf, int &read_errno);
};

#endif	/* DEVICE_H */

