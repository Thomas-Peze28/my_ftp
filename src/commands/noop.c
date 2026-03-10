/*
** EPITECH PROJECT, 2024
** Project
** File description:
** noop command
*/

#include "client.h"

void noop_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args)
{
    (void)clients;
    (void)args;
    ftp_response(fds[client_index].fd, "200 NOOP command successful\r\n");
}
