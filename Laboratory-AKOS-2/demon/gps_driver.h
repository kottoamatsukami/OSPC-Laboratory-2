#pragma once

#define MAX_SLEEP_TIME 1000000
#define MAX_SATTELITE_NAME_LENGHT 64
#define MAX_SATTELITE_COUNT 16

typedef struct {
	char name[MAX_SATTELITE_NAME_LENGHT];
	double latitude;
	double longitude;
} gps_sattelite_t;


gps_sattelite_t gps_driver_get_coordinates(char* name);

int is_name_available(char *name);

int is_sattelite_exists(char *name);

void create_sattelite(char *name);

void destroy_sattelite(char *name);

void print_all();


