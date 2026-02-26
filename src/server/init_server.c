/*
** EPITECH PROJECT, 2024
** Project
** File description:
** init_server
*/

#include "server.h"

int init_server(int port)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;

    if (socket_fd == -1)
        return return_error("Failed to create socket", -1);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        close(socket_fd);
        return return_error("Failed to bind socket", -1);
    }
    if (listen(socket_fd, MAX_CLIENTS) == -1) {
        close(socket_fd);
        return return_error("Failed to listen on socket", -1);
    }
    return socket_fd;
}
