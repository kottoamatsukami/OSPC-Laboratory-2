cmake_minimum_required(VERSION 3.25)
project(OSPC_Laboratory_2 C)

set(CMAKE_C_STANDARD 11)

include_directories(core)
include_directories(demon)
include_directories(driver)

add_executable(OSPC_Laboratory_2
        core/stuff.c
        core/stuff.h
        demon/daemon.c
        demon/daemon.h
        driver/gps_driver.c
        driver/gps_driver.h
        client_application.c core/config.h)
