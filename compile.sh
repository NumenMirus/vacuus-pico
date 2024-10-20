#!/bin/bash

mkdir build
cd build

export PICO_SDK_PATH=../pico-sdk
#export PICO_TOOLCHAIN_PATH=$(dirname $(which arm-none-eabi-gcc))

cmake ..

make -j4

if [ "$1" == "run" ]; then
    cp *.uf2 /media/$USER/RPI-RP2
    sleep 2
    sudo chmod 666 /dev/ttyACM0
fi