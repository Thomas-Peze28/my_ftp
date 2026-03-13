/*
** EPITECH PROJECT, 2024
** Project
** File description:
** init_clients
*/

#include "server.h"

void init_clients(server_t *server, char *path)
{
    char real_path[PATH_MAX];

    if (realpath(path, real_path) != NULL) {
        server->home_dir = strdup(real_path);
    } else {
        server->home_dir = strdup(path);
    }
    for (int i = 1; i < MAX_CLIENTS; i++) {
        server->clients[i].fd = -1;
        server->clients[i].is_logged = false;
        server->clients[i].username = NULL;
        server->clients[i].current_dir = NULL;
        server->fds[i].fd = -1;
        server->fds[i].events = POLLIN;
    }
}
