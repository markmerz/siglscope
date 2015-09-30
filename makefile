CC=g++
# CCFLAGS=-std=c++11 -Wall -g
CCFLAGS=-std=c++11 -Wall -O2

all: usbtmc_command accwave_siglentsds1000 accspectrum_siglentsds1000 siglscope

usbtmc_command: Device.o usbtmc_command.o
	$(CC) $(CCFLAGS) -o usbtmc_command Device.o usbtmc_command.o
	
accwave_siglentsds1000: Device.o Wave.o accwave_siglentsds1000.o
	$(CC) $(CCFLAGS) -o accwave_siglentsds1000 -lfftw3 Device.o Wave.o accwave_siglentsds1000.o
	
accspectrum_siglentsds1000: Device.o Wave.o accspectrum_siglentsds1000.o
	$(CC) $(CCFLAGS) -o accspectrum_siglentsds1000 -lfftw3 Device.o Wave.o accspectrum_siglentsds1000.o

clean:
	rm -f *.o usbtmc_command accwave_siglentsds1000 accspectrum_siglentsds1000 siglscope Makefile.qt

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

siglscope:
	/usr/lib64/qt5/bin/qmake -makefile -o Makefile.qt SiglScope.pro
	make -f Makefile.qt

