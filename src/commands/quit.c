/*
** EPITECH PROJECT, 2024
** Project
** File description:
** quit command
*/

#include "server.h"

void quit_command(server_t *server, int client_index, char **args)
{
    (void)args;
    disconnect_client(server, client_index);
    ftp_response(server->fds[client_index].fd, FTP_GOODBYE);
}
