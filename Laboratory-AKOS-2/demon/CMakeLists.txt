cmake_minimum_required(VERSION 3.22)

project(gps_daemon)

add_executable(demon
		daemon.c
		daemon.h
		gps_driver.c
		gps_driver.h
)
