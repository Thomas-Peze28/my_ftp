/*
** EPITECH PROJECT, 2024
** Project
** File description:
** main
*/

#include "myftp.h"

int connection(int socket_fd, struct sockaddr_in client_address, socklen_t client_address_len)
{
    int accept_result = accept(socket_fd, (struct sockaddr *)&client_address, &client_address_len);

    if (accept_result == -1) {
        printf("Failed to accept connection\n");
        return 84;
    } else {
        printf("Connection from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
    }
    return accept_result;
}

int response(int accept_result)
{
    write(accept_result, "Hello Client!\n", strlen("Hello Client!\n"));
    sleep(5);
    write(accept_result, "Goodbye Client!\n", strlen("Goodbye Client!\n"));
    close(accept_result);
    return 0;
}

int myftp(int port, char *path)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1) {
        printf("Failed to create socket\n");
        return 84;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    int bind_result = bind(socket_fd, (struct sockaddr *)&address, sizeof(address));

    if (bind_result == -1) {
        printf("Failed to bind socket\n");
        return 84;
    }

    int listen_result = listen(socket_fd, 0);

    if (listen_result == -1) {
        printf("Failed to listen on socket\n");
        return 84;
    }

    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
    int accept_result = 0;

    while (1) {
        accept_result = connection(socket_fd, client_address, client_address_len);
        pid_t pid = fork();

        if (pid == -1) {
            printf("Failed to fork process\n");
            return 84;
        } else if (pid == 0) {
            close(socket_fd);
            response(accept_result);
            exit(EXIT_SUCCESS);
        } else {
            close(accept_result);
        }
        
    }
    close(socket_fd);
    return 0;
}

int main(int argc, char **argv)
{
    int port = 0;

    if (handle_errors(argc, argv))
        return 84;
    port = atoi(argv[1]);
    myftp(port, argv[2]);
    return 0;
}
