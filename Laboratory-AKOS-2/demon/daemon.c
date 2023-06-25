#include "daemon.h"
#include "gps_driver.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>



int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from GPS daemon";
    gps_sattelite_t coordinates;

    // Создание сокета
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return 1;
    }

    // Настройка сокета
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        return 1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Привязка сокета к адресу и порту
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        return 1;
    }
    
	printf("GPS Demon is working, listening...\n");
	while (1)
	{
		// Ожидание подключения клиента
		if (listen(server_fd, 3) < 0) {
		    perror("listen");
		    return 1;
		}
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
		    perror("accept");
		    return 1;
		}
		printf("Someone has connected\n");
		// Обработка запросов клиента
		
		char command[COMMAND_LENGHT], identifier[IDENT_LENGHT];
		int fill_id = 0;
		while (1) {
		    valread = read(new_socket, buffer, 1024);
		    if (valread <= 0) {
		        break;
		    }
		    // Clear cache
		    for (int i = 0; i < COMMAND_LENGHT; i++)
		    {
		   		command[i] = '\0';
		    }
		    for (int i = 0; i < IDENT_LENGHT; i++)
		    {
		    	identifier[i] = '\0';
		    }
		    
		    // Parse command
		    for (int i = 0; i < strlen(buffer); i++)
		    {
		    	if (buffer[i] == ' ')
		    	{
		    		fill_id = 1;
		    	}
		    	else
		    	{
		    		if (fill_id == 0) // Fill command
		    		{
		    			command[i] = buffer[i];
		    		}
		    		else			  // Fill argument
		    		{
		    			identifier[i - strlen(command) - 1] = buffer[i];
		    		}
		    	}
		    }
		    
		    // Clear cache
		    strcpy(buffer, "");
		    
		    // Parse commands
		    if (strcmp(command, "launch") == 0)
		    {
		    	if (is_name_available(identifier))
		    	{
		    		// ERRORS
		    		if (rand()%LAUNCH_ERROR_PROBABILITY == 0)
		    		{
		    			int variant = rand()%4;
		    			if (variant == 0)
		    			{strcpy(buffer, "ERROR: The rocket crashed");}
		    			if (variant == 1)
		    			{strcpy(buffer, "ERROR: Satellite show down by the pendosi");}
		    			if (variant == 2)
		    			{strcpy(buffer, "ERROR: Satellite hit by space debris");}
		    			if (variant == 3)
		    			{strcpy(buffer, "ERROR: Critical damage during unhoocking");}
		    		}
		    		else
		    		{
						create_sattelite(identifier);
						strcpy(buffer, "Done");
		    		}
		    	}
		    	else
		    	{
		    		strcpy(buffer, "ERROR: The sattelite with this name is already exists");
		    	}
		    }
		    else if (strcmp(command, "destroy") == 0)
		    {
		    	if (!is_name_available(identifier))
		    	{	
		    		// ERRORS
		    		if (rand()%DESTROY_ERROR_PROBABILITY == 0)
		    		{
		    			int variant = rand()%2;
		    			if (variant == 0)
		    			{strcpy(buffer, "ERROR: In communication with the satellite");}
		    			if (variant == 1)
		    			{strcpy(buffer, "ERROR: Unstable connection");}
		    		}
		    		else
		    		{
						destroy_sattelite(identifier);
						strcpy(buffer, "Done");
		    		}
		    	}
		    	else
		    	{
		    		strcpy(buffer, "ERROR: This sattelite is not exists");
		    	}
		    }
		    else if (strcmp(command, "change_orbit") == 0)
		    {
		    	if (!is_name_available(identifier))
		    	{
		    		// ERRORS
		    		if (rand()%ORBIT_ERROR_PROBABILITY == 0)
		    		{
		    			int variant = rand()%3;
		    			if (variant == 0)
		    			{strcpy(buffer, "ERROR: In communication with the satellite");}
		    			if (variant == 1)
		    			{strcpy(buffer, "ERROR: Unstable connection");}
		    			if (variant == 2)
		    			{strcpy(buffer, "ERROR: The orbit is busy");}
		    		}
		    		else
		    		{
		    			strcpy(buffer, "Changed");
		    		}
		    	}
		    	else
		    	{
		    		strcpy(buffer, "ERROR: This sattelite is not exists");
		    	}
		    }
		    else if (strcmp(command, "get_coords") == 0)
		    {
		    	if (!is_name_available(identifier))
		    	{	
		    		// ERRORS
		    		if (rand()%GET_ERROR_PROBABILITY == 0)
		    		{
		    			int variant = rand()%2;
		    			if (variant == 0)
		    			{strcpy(buffer, "ERROR: In communication with the satellite");}
		    			if (variant == 1)
		    			{strcpy(buffer, "ERROR: Unstable connection");}
		    		}
		    		else
		    		{
						coordinates = gps_driver_get_coordinates(identifier);
						char *log = (char*)malloc(1024*sizeof(char));
						sprintf(log, "The coords is: [latitude]=%lf | [longitude]=%lf", coordinates.latitude, coordinates.longitude);
						strcpy(buffer, log);
					}
		    	}
		    	else
		    	{
		    		strcpy(buffer, "ERROR: This sattelite is not exists");
		    	}
		    }
		    else
		    {
		    	printf("Unknow command: %s\n", command);
		    }
		    
		    print_all();
		    send(new_socket, buffer, 1024, 0);
		    fill_id = 0;
		}
	}
	// Закрытие сокета
	close(new_socket);
	close(server_fd);
    return 0;
}
