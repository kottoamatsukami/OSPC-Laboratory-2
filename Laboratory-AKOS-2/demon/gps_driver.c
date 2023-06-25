#include "gps_driver.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

static gps_sattelite_t available_sattelites[MAX_SATTELITE_COUNT];
int in_orbit = 0;


int is_name_available(char *name)
{
	for (int i = 0; i < in_orbit; i++)
	{
		if (strcmp(name, available_sattelites[i].name) == 0)
		{ return 0;}
	} 
	return 1;
}

int is_sattelite_exists(char *name)
{
	for (int i = 0; i < in_orbit; i++)
	{
		if (strcmp(name, available_sattelites[i].name) == 0)
		{ return 1;}
	} 
	return 0;
}


void create_sattelite(char *name)
{
	if (in_orbit >= MAX_SATTELITE_COUNT)
	{
		return;
	}
	gps_sattelite_t *new = malloc(sizeof(gps_sattelite_t));
	strcpy(new->name, name);
	available_sattelites[in_orbit] = *new;
	in_orbit++;
	printf("Create new sattelite [%s], in orbit: [%d]\n", new->name, in_orbit);
}

void destroy_sattelite(char *name)
{
	int i = 0;
	for (; i < in_orbit; i++)
	{
		if (strcmp(name, available_sattelites[i].name) == 0)
		{
			strcpy(available_sattelites[i].name, "");
			in_orbit--;
			printf("Destroyed a sattelite [%s], in orbit: [%d]\n", name, in_orbit);
			break;
		}
	}
	for (int j = i; j < in_orbit; j++)
	{
		available_sattelites[j] = available_sattelites[j+1];
	}
}

void print_all()
{
	for (int i = 0; i < in_orbit; i++)
    {
    	printf("S[%d]: %s\n", i, available_sattelites[i].name);
    }
}

gps_sattelite_t gps_driver_get_coordinates(char* name) {
    // Запрос координат у GPS-модуля
    // Обработка полученных координат
    // Имитация задержки ответа от устройства
    usleep(MAX_SLEEP_TIME);
    srand(time(NULL));
    for (int i = 0; i < in_orbit; i++)
    {
    	if (strcmp(name, available_sattelites[i].name) == 0)
    	{
    		available_sattelites[i].latitude = rand() % 180 - 90;
    		available_sattelites[i].longitude = rand() % 360 - 180;
    		return available_sattelites[i];
    	}
    }
}
