#!/bin/bash
KEYMAP=$1
qmk --version || nix-shell
#qmk compile -kb ferris/sweep -km $KEYMAP -e CONVERT_TO=liatris || exit 1
rm -frv *.uf2
qmk compile -kb splitkb/aurora/lily58 -km $KEYMAP -e CONVERT_TO=liatris || exit 1
echo "Firmware compiled."
echo "Please enter password for sudo."
sudo -v

FILE=$(ls -1rt --sort=time|grep ".uf2"|tail -n 1)
echo -e "Using firmware $FILE\n"

# Flash first half
read -p "Connect first part of keyboard and set it in boot/flash mode." || exit

DEVICE=$(lsblk --output=path,id,label --filter 'LABEL=="RPI-RP2" && TYPE=="part"'|tail -n 1|awk '{print $1}')

echo "Using device $DEVICE"
lsblk $DEVICE -o PATH,LABEL,ID,FSTYPE,SIZE,MOUNTPOINTS

echo
read -p "Confirm writing $FILE to $DEVICE" || exit

sudo sh -c "cat $FILE > $DEVICE" &&
echo -e "First half of keyboard successfully flashed\n"

# Flash second half
read -p "Please connect second half and set it in boot/flash mode." || exit

DEVICE=$(lsblk --output=path,id,label --filter 'LABEL=="RPI-RP2" && TYPE=="part"'|tail -n 1|awk '{print $1}')

echo "Using device $DEVICE"
lsblk $DEVICE -o PATH,LABEL,ID,FSTYPE,SIZE,MOUNTPOINTS

echo
read -p "Confirm writing $FILE to $DEVICE" || exit

sudo sh -c "cat $FILE > $DEVICE" &&
echo "Second half of keyboard successfully flashed"
echo "Firmware update completed"
