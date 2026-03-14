/*
** EPITECH PROJECT, 2024
** Project
** File description:
** list command
*/

#include "server.h"

int check_list_command(server_t *server, int client_index)
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
    return 0;
}

int command_ls(server_t *server, int client_index, int data_fd, char *path)
{
    pid_t pid = fork();

    if (pid == -1)
        return -1;
    if (pid == 0) {
        dup2(data_fd, STDOUT_FILENO);
        close(data_fd);
        close(server->clients[client_index].data_fd);
        execl("/bin/ls", "ls", "-l", path, NULL);
        exit(0);
    } else {
        close(data_fd);
        waitpid(pid, NULL, 0);
        close(server->clients[client_index].data_fd);
        server->clients[client_index].data_fd = -1;
        server->clients[client_index].state = INACTIVE;
        ftp_response(server->fds[client_index].fd, FTP_DIR_SEND_OK);
    }
    return 0;
}

char *check_path(server_t *server, int client_index, char **args)
{
    char target_path[PATH_MAX];
    char resolved_path[PATH_MAX];

    if (args[1] == NULL)
        return strdup(server->clients[client_index].current_dir);
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

void list_command(server_t *server, int client_index, char **args)
{
    char *path = NULL;
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int data_sock = -1;

    if (check_list_command(server, client_index) == -1)
        return;
    path = check_path(server, client_index, args);
    if (check_path_error(server, client_index, path) == -1)
        return;
    data_sock = accept(server->clients[client_index].data_fd,
        (struct sockaddr *)&client_addr, &addr_len);
    if (check_data_sock(server, client_index, data_sock, path) == -1)
        return;
    ftp_response(server->fds[client_index].fd, FTP_FILE_STATUS);
    command_ls(server, client_index, data_sock, path);
    free(path);
}
