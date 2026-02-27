/*
** EPITECH PROJECT, 2024
** Project
** File description:
** user command
*/

#include "client.h"

void user_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args)
{
    if (clients[client_index].is_logged)
        return ftp_response(fds[client_index].fd, FTP_REAUTH_FAIL);
    if (args[1] == NULL)
        return ftp_response(fds[client_index].fd, FTP_NEED_USER);
    free(clients[client_index].username);
    clients[client_index].username = strdup(args[1]);
    return ftp_response(fds[client_index].fd, FTP_USER_OK);
}
