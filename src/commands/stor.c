/*
** EPITECH PROJECT, 2024
** Project
** File description:
** stor command
*/

#include "server.h"
#include <fcntl.h>

int check_stor_command(server_t *server, int client_index, char **args)
{
    if (!server->clients[client_index].is_logged) {
        ftp_response(server->fds[client_index].fd, FTP_NOT_LOGGED_IN);
        return -1;
    }
    if (server->clients[client_index].data_fd == -1) {
        ftp_response(server->fds[client_index].fd, FTP_DATA_CONNECTION);
        return -1;
    }
    if (server->clients[client_index].state != PASSIVE
        && server->clients[client_index].state != ACTIVE) {
        ftp_response(server->fds[client_index].fd, FTP_BAD_SEQUENCE);
        return -1;
    }
    if (args[1] == NULL) {
        ftp_response(server->fds[client_index].fd, FTP_NEED_ARG);
        return -1;
    }
    return 0;
}

void stor_child(server_t *server, int client_index, int data_fd, char *path)
{
    int file_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char buffer[1];
    ssize_t bytes_read = 0;

    if (file_fd == -1) {
        ftp_response(server->fds[client_index].fd, FTP_FILE_UNAVAILABLE);
        close(data_fd);
        exit(1);
    }
    bytes_read = read(data_fd, buffer, sizeof(buffer));
    while (bytes_read > 0) {
        write(file_fd, buffer, bytes_read);
        bytes_read = read(data_fd, buffer, sizeof(buffer));
    }
    close(file_fd);
    close(data_fd);
    close(server->clients[client_index].data_fd);
    exit(0);
}

void stor_parent(server_t *server, int client_index, int data_fd, pid_t pid)
{
    close(data_fd);
    waitpid(pid, NULL, 0);
    close(server->clients[client_index].data_fd);
    server->clients[client_index].data_fd = -1;
    server->clients[client_index].state = INACTIVE;
    ftp_response(server->fds[client_index].fd, FTP_TRANSFER_OK);
}

int command_stor(server_t *server, int client_index, int data_fd, char *path)
{
    pid_t pid = fork();

    if (pid == -1)
        return -1;
    if (pid == 0) {
        stor_child(server, client_index, data_fd, path);
    } else {
        stor_parent(server, client_index, data_fd, pid);
    }
    return 0;
}

void stor_command(server_t *server, int client_index, char **args)
{
    char *path = NULL;
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int data_sock = -1;

    if (check_stor_command(server, client_index, args) == -1)
        return;
    path = check_stor_path(server, client_index, args);
    if (check_path_error(server, client_index, path) == -1)
        return;
    data_sock = accept(server->clients[client_index].data_fd,
        (struct sockaddr *)&client_addr, &addr_len);
    if (check_data_sock(server, client_index, data_sock, path) == -1)
        return;
    ftp_response(server->fds[client_index].fd, FTP_FILE_STATUS);
    command_stor(server, client_index, data_sock, path);
    free(path);
}
