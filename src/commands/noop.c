/*
** EPITECH PROJECT, 2024
** Project
** File description:
** noop command
*/

#include "server.h"

void noop_command(server_t *server, int client_index, char **args)
{
    (void)args;
    ftp_response(server->fds[client_index].fd,
        "200 NOOP command successful\r\n");
}
