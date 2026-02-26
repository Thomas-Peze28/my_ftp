/*
** EPITECH PROJECT, 2024
** Project
** File description:
** disconnet_client
*/

#include "client.h"

void disconnect_client(int index, client_t *clients, struct pollfd *fds)
{
    if (fds[index].fd != -1) {
        dprintf(fds[index].fd, "Server: Goodbye!\r\n");
        close(fds[index].fd);
        fds[index].fd = -1;
        clients[index].fd = -1;
        clients[index].is_logged = false;
        free(clients[index].username);
        free(clients[index].path);
        clients[index].username = NULL;
        clients[index].path = NULL;
        printf("Client on slot %d disconnected.\n", index);
    }
}
