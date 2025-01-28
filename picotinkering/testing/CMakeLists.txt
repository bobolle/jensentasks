cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD pico_w)

include(pico_sdk_import.cmake)

project(testing C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(pico_ultrasonic_lib)

add_executable(testing
    testing.c
)

pico_enable_stdio_usb(testing 1)
pico_enable_stdio_uart(testing 1)

pico_add_extra_outputs(testing)

target_link_libraries(testing 
    pico_stdlib
    pico_ultrasonic_lib
)
