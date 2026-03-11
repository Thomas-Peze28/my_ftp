/*
** EPITECH PROJECT, 2024
** Project
** File description:
** disconnect_client
*/

#include "client.h"

void disconnect_client(int index, client_t *clients, struct pollfd *fds)
{
    if (fds[index].fd != -1) {
        ftp_response(fds[index].fd, FTP_GOODBYE);
        close(fds[index].fd);
        fds[index].fd = -1;
        clients[index].fd = -1;
        clients[index].is_logged = false;
        free(clients[index].username);
        free(clients[index].current_dir);
        free(clients[index].home_dir);
        clients[index].username = NULL;
        clients[index].current_dir = NULL;
        clients[index].home_dir = NULL;
        printf("Client on slot %d disconnected.\n", index);
    }
}
