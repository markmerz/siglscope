#!/bin/bash

found_hook=1
for hook in /dev/usbtmc*; do
	device=$(usbtmc_command --device ${hook} -- '*IDN?')
	if [[ $device =~ 'SDS1102CML' ]]; then
		found_hook=0
		break
	fi
done
if [ "$found_hook" != "0" ]; then
	echo "DSO was not found.." > /dev/stderr
	exit 1
fi

tempdir=$(mktemp -d)
usbtmc_command --device ${hook} -- SCDP > ${tempdir}/image.bmp

newfilename=$(date '+SiglentDSO_Screenshot_%Y%m%d_%H%M%S.png')
convert -quiet ${tempdir}/image.bmp $newfilename 2>/dev/null
echo $newfilename
rm ${tempdir}/image.bmp
rmdir ${tempdir}

