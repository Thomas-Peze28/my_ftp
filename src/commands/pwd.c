/*
** EPITECH PROJECT, 2024
** Project
** File description:
** pwd command
*/

#include "server.h"

void pwd_command(server_t *server, int client_index, char **args)
{
    int home_len = 0;
    char *virtual_path = NULL;

    (void)args;
    if (!server->clients[client_index].is_logged)
        return ftp_response(server->fds[client_index].fd, FTP_NOT_LOGGED_IN);
    home_len = strlen(server->home_dir);
    virtual_path = server->clients[client_index].current_dir + home_len;
    if (strlen(virtual_path) == 0)
        virtual_path = "/";
    dprintf(server->fds[client_index].fd,
        "257 \"%s\" is the current directory\r\n",
        virtual_path);
}
