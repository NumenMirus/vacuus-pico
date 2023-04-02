cmake_minimum_required(VERSION 3.25)

include(build/pico_sdk_import.cmake)

project(vacuus_pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(vacuus_pico
        main.c)

target_link_libraries(vacuus_pico pico_stdlib pico_cyw43_arch_none)

pico_add_extra_outputs(vacuus_pico)
