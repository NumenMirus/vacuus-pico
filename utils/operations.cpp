#include "sd.hpp"
#include "pico/stdlib.h"
#include <cstdlib>
#include <cstdio>

void test() {
    printf("---- Entered test function ------------------\n");

    // Test SD card
    printf("Mounting SD card...\n");
    mount_sd_card();

    printf("---- Exited test function -------------------\n");
}