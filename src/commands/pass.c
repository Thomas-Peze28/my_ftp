/*
** EPITECH PROJECT, 2024
** Project
** File description:
** pass command
*/

#include "commands.h"
#include "client.h"

int is_valid_password(const char *username, const char *password)
{
    if (strcmp(username, "Anonymous") == 0 && password == NULL)
        return 1;
    return 0;
}

void pass_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args)
{
    if (clients[client_index].is_logged)
        return ftp_response(fds[client_index].fd, FTP_ALREADY_LOGIN);
    if (is_valid_password(clients[client_index].username, args[1])) {
        clients[client_index].is_logged = true;
        return ftp_response(fds[client_index].fd, FTP_LOGIN_OK);
    }
    if (args[1] == NULL)
        return ftp_response(fds[client_index].fd, FTP_NEED_PASS);
    if (clients[client_index].username == NULL)
        return ftp_response(fds[client_index].fd, FTP_BAD_SEQUENCE);
    return ftp_response(fds[client_index].fd, FTP_BAD_LOGIN);
}
