/*
** EPITECH PROJECT, 2024
** Project
** File description:
** cwd command
*/

#include "client.h"

int check_cwd_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args)
{
    if (!clients[client_index].is_logged) {
        ftp_response(fds[client_index].fd, FTP_NOT_LOGGED_IN);
        return -1;
    }
    if (args[1] == NULL) {
        ftp_response(fds[client_index].fd, FTP_NEED_ARG);
        return -1;
    }
    return 0;
}

void cwd_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args)
{
    char target_path[PATH_MAX];
    char resolved_path[PATH_MAX];

    if (check_cwd_command(client_index, clients, fds, args) == -1)
        return;
    if (args[1][0] == '/')
        snprintf(target_path, sizeof(target_path), "%s%s",
            clients[client_index].home_dir, args[1]);
    else
        snprintf(target_path, sizeof(target_path), "%s/%s",
            clients[client_index].current_dir, args[1]);
    if (realpath(target_path, resolved_path) == NULL)
        return ftp_response(fds[client_index].fd, FTP_DIR_CHANGE_FAIL);
    if (strncmp(resolved_path, clients[client_index].home_dir,
        strlen(clients[client_index].home_dir)) != 0) {
        return ftp_response(fds[client_index].fd, FTP_OUT_OF_ROOT);
    }
    free(clients[client_index].current_dir);
    clients[client_index].current_dir = strdup(resolved_path);
    ftp_response(fds[client_index].fd, FTP_DIR_CHANGED);
}
