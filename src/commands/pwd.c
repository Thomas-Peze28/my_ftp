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
    int home_len = 0;
    char *virtual_path = NULL;

    (void)args;
    if (!clients[client_index].is_logged)
        return ftp_response(fds[client_index].fd, FTP_NOT_LOGGED_IN);
    home_len = strlen(clients[client_index].home_dir);
    virtual_path = clients[client_index].current_dir + home_len;
    if (strlen(virtual_path) == 0)
        virtual_path = "/";
    dprintf(fds[client_index].fd, "257 \"%s\" is the current directory\r\n",
        virtual_path);
}
