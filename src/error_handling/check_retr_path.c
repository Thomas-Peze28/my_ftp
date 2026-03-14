/*
** EPITECH PROJECT, 2024
** Project
** File description:
** retr command
*/

#include "server.h"

char *check_retr_path(server_t *server, int client_index, char **args)
{
    char target_path[PATH_MAX];
    char resolved_path[PATH_MAX];

    if (args[1][0] == '/')
        snprintf(target_path, sizeof(target_path), "%s%s", HOME, args[1]);
    else
        snprintf(target_path, sizeof(target_path), "%s/%s",
            server->clients[client_index].current_dir, args[1]);
    if (realpath(target_path, resolved_path) == NULL) {
        ftp_response(server->fds[client_index].fd, FTP_FILE_UNAVAILABLE);
        return NULL;
    }
    if (strncmp(resolved_path, HOME, strlen(HOME)) != 0) {
        ftp_response(server->fds[client_index].fd, FTP_OUT_OF_ROOT);
        return NULL;
    }
    return strdup(resolved_path);
}
