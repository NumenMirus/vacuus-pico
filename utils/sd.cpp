#include <stdio.h>
#include "pico/stdlib.h"
#include "ff.h"
#include "sd_card.h"
#include "sd.hpp"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "diskio.h"

FATFS fs; // Filesystem object

bool init_sd(){

    FRESULT fr;
    FATFS fs;
    FIL fil;
    int ret;
    char buffer[100];
    char filename[] = "db.sqlite3";

    if(!sd_init_driver()) {
    printf("Failed to initialize SD card driver.\n");
    return false;
    }


    fr = f_mount(&fs, "0:", 1);
    if(fr == FR_OK) {
        printf("Filesystem mounted successfully.\n");
    } else if( fr == FR_DISK_ERR) {
        printf("The lower layer, disk_read, disk_write or disk_ioctl function, reported that an unrecoverable hard error occured.\n");
    } else if( fr == FR_NOT_READY) {
        printf("The physical drive cannot work.\n");
    } else if( fr == FR_NO_FILESYSTEM) {
        printf("There is no valid FAT volume on the drive.\n");
    } else if( fr == FR_INVALID_DRIVE) {
        printf("The drive number is invalid.\n");
    } else if( fr == FR_INVALID_PARAMETER) {
        printf("The path name format is invalid.\n");
    } else {
        printf("Failed to mount filesystem: %d\n", fr);
        return false;
    }

    return true;
}

bool test_sd_card() {
    if (!init_sd()) {
        return false;
    }

    return true;
}