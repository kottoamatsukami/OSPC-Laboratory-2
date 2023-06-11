#include "gps_driver.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static gps_coordinates_t current_coordinates = {0};

int gps_driver_init() {
    // Инициализация GPS-модуля
    return 0;
}

void gps_driver_deinit() {
    // Деинициализация GPS-модуля
}

gps_coordinates_t gps_driver_get_coordinates() {
    // Запрос координат у GPS-модуля
    // Обработка полученных координат
    // Имитация задержки ответа от устройства
    usleep(100000);
    current_coordinates.latitude = rand() % 180 - 90;
    current_coordinates.longitude = rand() % 360 - 180;
    return current_coordinates;
}