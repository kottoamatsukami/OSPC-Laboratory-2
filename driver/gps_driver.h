#pragma once

typedef struct {
    double latitude;
    double longitude;
} gps_coordinates_t;

int gps_driver_init();

void gps_driver_deinit();

gps_coordinates_t gps_driver_get_coordinates();
