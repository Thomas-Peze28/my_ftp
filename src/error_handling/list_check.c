/*
** EPITECH PROJECT, 2024
** Project
** File description:
** cwd command
*/

#include "server.h"

int check_data_sock(server_t *server, int client_index, int data_sock,
    char *path)
{
    if (data_sock == -1) {
        ftp_response(server->fds[client_index].fd, FTP_DATA_CONNECTION);
        free(path);
        close(server->clients[client_index].data_fd);
        server->clients[client_index].data_fd = -1;
        server->clients[client_index].state = INACTIVE;
        return -1;
    }
    return 0;
}

int check_path_error(server_t *server, int client_index, char *path)
{
    if (path == NULL) {
        free(path);
        close(server->clients[client_index].data_fd);
        server->clients[client_index].data_fd = -1;
        server->clients[client_index].state = INACTIVE;
        return -1;
    }
    return 0;
}
