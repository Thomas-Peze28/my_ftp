/*
** EPITECH PROJECT, 2024
** Project
** File description:
** dele command
*/

#include "server.h"

int check_dele_command(server_t *server, int client_index, char **args)
{
    if (!server->clients[client_index].is_logged) {
        ftp_response(server->fds[client_index].fd, FTP_NOT_LOGGED_IN);
        return -1;
    }
    if (args[1] == NULL) {
        ftp_response(server->fds[client_index].fd, FTP_NEED_ARG);
        return -1;
    }
    return 0;
}

void dele_command(server_t *server, int client_index, char **args)
{
    char target_path[PATH_MAX];
    char resolved_path[PATH_MAX];

    if (check_dele_command(server, client_index, args) == -1)
        return;
    snprintf(target_path, sizeof(target_path), "%s/%s",
        server->clients[client_index].current_dir, args[1]);
    if (realpath(target_path, resolved_path) == NULL)
        return ftp_response(server->fds[client_index].fd,
            FTP_FILE_DELETE_FAIL);
    if (strncmp(resolved_path, server->home_dir,
        strlen(server->home_dir)) != 0)
        return ftp_response(server->fds[client_index].fd,
            FTP_OUT_OF_ROOT);
    if (remove(resolved_path) == 0)
        ftp_response(server->fds[client_index].fd, FTP_FILE_DELETED);
    else
        ftp_response(server->fds[client_index].fd, FTP_FILE_DELETE_FAIL);
}
