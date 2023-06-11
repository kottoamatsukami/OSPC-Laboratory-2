#include "daemon.h"

#include "gps_driver.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from GPS daemon";
    gps_coordinates_t coordinates;

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

    // Ожидание подключения клиента
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return 1;
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        return 1;
    }

    // Обработка запросов клиента
    while (1) {
        valread = read(new_socket, buffer, 1024);
        if (valread <= 0) {
            break;
        }
        coordinates = gps_driver_get_coordinates();
        sprintf(buffer, "Latitude: %f, Longitude: %f", coordinates.latitude, coordinates.longitude);
        send(new_socket, buffer, strlen(buffer), 0);
    }

    // Закрытие сокета и драйвера
    close(new_socket);
    close(server_fd);
    gps_driver_deinit();

    return 0;
}