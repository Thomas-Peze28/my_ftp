/*
** EPITECH PROJECT, 2024
** Project
** File description:
** pwd command
*/

#include "client.h"

void pwd_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args)
{
    (void)args;
    if (!clients[client_index].is_logged)
        return ftp_response(fds[client_index].fd, FTP_NOT_LOGGED_IN);
    dprintf(fds[client_index].fd, "257 \"%s\" is the current directory\r\n",
        clients[client_index].path);
}
