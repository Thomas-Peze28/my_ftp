/*
** EPITECH PROJECT, 2024
** Project
** File description:
** init_server
*/

#include "server.h"

int init_server_fd(int port)
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

void init_server_socket(server_t *server, int port)
{
    server->fds[0].fd = server->socket_fd;
    server->fds[0].events = POLLIN;
    printf("Server is listening on port %d\n", port);
}

int init_server(server_t *server, int port)
{
    server->port = port;
    server->socket_fd = init_server_fd(port);
    if (server->socket_fd == -1)
        return -1;
    server->current_clients = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->clients[i].fd = -1;
        server->fds[i].fd = -1;
        server->fds[i].events = 0;
    }
    server->home_dir = NULL;
    init_server_socket(server, port);
    return server->socket_fd;
}
