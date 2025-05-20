#!/bin/bash
KEYMAP=$1
qmk --version || nix-shell
#qmk compile -kb ferris/sweep -km $KEYMAP -e CONVERT_TO=liatris || exit 1
rm -frv *.uf2
qmk compile -kb splitkb/aurora/lily58 -km $KEYMAP -e CONVERT_TO=liatris || exit 1
echo "Firmware compiled."
echo "Please enter password for sudo."
sudo -v
echo "Connect first part of keyboard and set it in boot/flash mode."

FILE=$(ls -1rt --sort=time|grep ".uf2"|tail -n 1)
echo "Using firmware $FILE"

# Flash first half
until sudo mount --source LABEL=RPI-RP2 --target /mnt --type vfat --options rw
do
  sleep 5
  echo "Failed to mount device, please connect it"
done

sudo cp -v $FILE /mnt &&
sleep 3 &&
echo "First half of keyboard successfully flashed"
sudo umount /mnt || exit 2

# Flash second half
echo "Please connect second half and set it in boot/flash mode."
sleep 5

until sudo mount --source LABEL=RPI-RP2 --target /mnt --type vfat --options rw
do
  sleep 5
  echo "Failed to mount device, please connect it"
done
sudo cp -v $FILE /mnt &&
sleep 3 &&
echo "Second half of keyboard successfully flashed"
sudo umount /mnt

echo "Firmware update completed"
