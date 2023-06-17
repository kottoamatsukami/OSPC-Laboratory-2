#include "client_application.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>



int main(int argc, char const *argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Создание сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Преобразование адреса и порта в структуру sockaddr_in
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Подключение к серверу
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("Daemon has reached!\n");
    greeting();

    // Отправка запросов на сервер
    while (1) {
    
    
        main_menu(); put_arrow();
        
        // get the command
        char input[64] = {0};
        
        fflush(stdin);
        scanf("%[^\n]%*c", input);
        
       	// exit
       	if (strcmp(input, "exit") == 0)
       	{
       		puts("Buy! Closing socket...");
       		break;
       	}
       	else
       	{
       		// working
       		puts(input);
    		send(sock, input, 1024, 0);
			valread = read(sock, buffer, 1024);
			printf("Daemon`s response is: %s\n", buffer);
       	}
       	// clear cache
       	strcpy(buffer, "");
       	strcpy(input, "");
    }

    // Закрытие сокета
    close(sock);
    return 0;
}

