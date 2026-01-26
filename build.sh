#!/bin/sh

# Like "splitkb/aurora/lily58" or "ferris/sweep"
KEYBOARD=$1
# Like "default", "debug", "qwerty_dfjk" or somethinge else
KEYMAP=$2

qmk --version || nix-shell -p qmk dos2unix
#qmk compile -kb ferris/sweep -km $KEYMAP -e CONVERT_TO=liatris || exit 1
rm -frv *.uf2
qmk compile -kb $KEYBOARD -km $KEYMAP -e CONVERT_TO=liatris || exit 1
echo "Firmware compiled."
