/*
** EPITECH PROJECT, 2024
** Project
** File description:
** quit command
*/

#include "client.h"

void quit_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args)
{
    (void)args;
    disconnect_client(client_index, clients, fds);
    ftp_response(fds[client_index].fd, FTP_GOODBYE);
}
