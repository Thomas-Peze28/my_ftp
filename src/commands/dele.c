/*
** EPITECH PROJECT, 2024
** Project
** File description:
** dele command
*/

#include "client.h"

int check_dele_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args)
{
    if (!clients[client_index].is_logged) {
        ftp_response(fds[client_index].fd, FTP_NOT_LOGGED_IN);
        return -1;
    }
    if (sizeof(args) < 2 || args[1] == NULL) {
        ftp_response(fds[client_index].fd, FTP_NEED_ARG);
        return -1;
    }
    return 0;
}

void dele_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args)
{
    char path[PATH_MAX];

    if (check_dele_command(client_index, clients, fds, args) == -1)
        return;

    snprintf(path, sizeof(path), "%s/%s", clients[client_index].current_dir, args[1]);

    if(remove(path) == 0) {
        ftp_response(fds[client_index].fd, FTP_FILE_DELETED);
    } else {
        ftp_response(fds[client_index].fd, FTP_FILE_DELETE_FAIL);
    }
}
