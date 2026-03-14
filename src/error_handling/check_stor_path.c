/*
** EPITECH PROJECT, 2024
** Project
** File description:
** stor command
*/

#include "server.h"

char *check_stor_path(server_t *server, int client_index, char **args)
{
    char target_path[PATH_MAX];

    if (strstr(args[1], "/") != NULL) {
        ftp_response(server->fds[client_index].fd, FTP_PATH_FAILED);
        return NULL;
    }
    snprintf(target_path, sizeof(target_path), "%s/%s",
        server->clients[client_index].current_dir, args[1]);
    return strdup(target_path);
}
