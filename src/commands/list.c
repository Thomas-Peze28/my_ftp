/*
** EPITECH PROJECT, 2024
** Project
** File description:
** list command
*/

#include "server.h"

int check_list_command(server_t *server, int client_index, char **args)
{
    if (!server->clients[client_index].is_logged) {
        ftp_response(server->fds[client_index].fd, FTP_NOT_LOGGED_IN);
        return -1;
    }
    if (args[1] != NULL) {
        ftp_response(server->fds[client_index].fd, FTP_NEED_ARG);
        return -1;
    }
    if (server->clients[client_index].data_fd == -1) {
        ftp_response(server->fds[client_index].fd, FTP_DATA_CONNECTION);
        return -1;
    }
    if (server->clients[client_index].state != PASSIVE && server->clients[client_index].state != ACTIVE) {
        ftp_response(server->fds[client_index].fd, FTP_BAD_SEQUENCE);
        return -1;
    }
    return 0;
}

int command_ls(server_t *server, int client_index, char *path)
{
    int data_fd = server->clients[client_index].data_fd;
    pid_t pid = fork();

    if (pid == -1) {
        ftp_response(server->fds[client_index].fd, FTP_DATA_CONNECTION);
        return -1;
    }
    if (pid == 0) {
        dup2(data_fd, STDOUT_FILENO);
        dup2(data_fd, STDERR_FILENO);
        close(data_fd);
        execl("/bin/ls", "ls", "-l", path, NULL);
        exit(EXIT_FAILURE);
    } else {
        close(data_fd);
        waitpid(pid, NULL, 0);
        ftp_response(server->fds[client_index].fd, "226 Directory send OK\r\n");
    }
    return 0;
}

int check_path(server_t *server, int client_index, char *target_path, char *resolved_path)
{
    if (realpath(target_path, resolved_path) == NULL) {
        ftp_response(server->fds[client_index].fd, FTP_DIR_CHANGE_FAIL);
        return -1;
    }
    if (strncmp(resolved_path, server->home_dir, strlen(server->home_dir)) != 0) {
        ftp_response(server->fds[client_index].fd, FTP_OUT_OF_ROOT);
        return -1;
    }
    return 0;
}


void list_command(server_t *server, int client_index, char **args)
{
    char target_path[PATH_MAX];
    char resolved_path[PATH_MAX];

    if (check_list_command(server, client_index, args) == -1)
        return;
    if (check_path(server, client_index, target_path, resolved_path) == -1)
        return;
    ftp_response(server->fds[client_index].fd, "150 File status okay; about to open data connection.\r\n");
    command_ls(server, client_index, resolved_path);
}
