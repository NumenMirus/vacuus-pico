cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(vacuus C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# pull in PICO SDK (must be before project)
set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# initialize the sdk
pico_sdk_init()

add_executable(vacuus
    main.c
)

# pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(vacuus pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(vacuus 1)
pico_enable_stdio_uart(vacuus 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(vacuus)