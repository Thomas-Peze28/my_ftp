/*
** EPITECH PROJECT, 2024
** Project
** File description:
** user command
*/

#include "server.h"

void user_command(server_t *server, int client_index, char **args)
{
    if (server->clients[client_index].is_logged)
        return ftp_response(server->fds[client_index].fd, FTP_REAUTH_FAIL);
    if (args[1] == NULL)
        return ftp_response(server->fds[client_index].fd, FTP_NEED_USER);
    free(server->clients[client_index].username);
    server->clients[client_index].username = strdup(args[1]);
    return ftp_response(server->fds[client_index].fd, FTP_USER_OK);
}
