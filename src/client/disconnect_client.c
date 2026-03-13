/*
** EPITECH PROJECT, 2024
** Project
** File description:
** disconnect_client
*/

#include "server.h"

void disconnect_client(server_t *server, int index)
{
    if (server->fds[index].fd != -1) {
        ftp_response(server->fds[index].fd, FTP_GOODBYE);
        close(server->fds[index].fd);
        server->fds[index].fd = -1;
        server->clients[index].fd = -1;
        server->clients[index].is_logged = false;
        free(server->clients[index].username);
        free(server->clients[index].current_dir);
        server->clients[index].username = NULL;
        server->clients[index].current_dir = NULL;
        printf("Client on slot %d disconnected.\n", index);
    }
}
