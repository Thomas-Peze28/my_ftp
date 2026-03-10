/*
** EPITECH PROJECT, 2024
** Project
** File description:
** init_clients
*/

#include "client.h"

void init_clients(client_t *clients, struct pollfd *fds, char *path)
{
    (void)path;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i].fd = -1;
        clients[i].is_logged = false;
        clients[i].username = NULL;
        clients[i].home_dir = NULL;
        clients[i].current_dir = NULL;
        fds[i].fd = -1;
        fds[i].events = POLLIN;
    }
}
