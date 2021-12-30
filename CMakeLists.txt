cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(my_pico_oled)

pico_sdk_init()

add_subdirectory(pico-ssd1306)

add_executable(clear
    clear.cpp
    )
target_link_libraries(clear
    pico_ssd1306
    hardware_i2c
    )
pico_add_extra_outputs(clear)

add_executable(oled
    main.cpp
    )
target_link_libraries(oled
    pico_ssd1306
    hardware_i2c
    )
pico_add_extra_outputs(oled)

add_executable(oled_ctrl
    control.cpp
    )
target_link_libraries(oled_ctrl
    pico_ssd1306
    pico_stdlib
    hardware_i2c
    )
pico_add_extra_outputs(oled_ctrl)