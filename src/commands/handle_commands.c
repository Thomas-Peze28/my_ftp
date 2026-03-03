/*
** EPITECH PROJECT, 2024
** Project
** File description:
** handle_client
*/

#include "commands.h"

int verify_auth(int client_index, client_t *clients, struct pollfd *fds)
{
    if (!clients[client_index].is_logged
        || clients[client_index].username == NULL) {
        ftp_response(fds[client_index].fd, FTP_NOT_LOGGED_IN);
        return -1;
    }
    if (clients[client_index].username != NULL
        && !clients[client_index].is_logged) {
        ftp_response(fds[client_index].fd, FTP_NOT_PASSED);
        return -1;
    }
    return 0;
}

char **get_client_command(int client_fd)
{
    char buffer[1024];
    int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);

    if (bytes_read <= 0)
        return NULL;
    buffer[bytes_read] = '\0';
    return parse_command(buffer);
}

void handle_commands(int client_index, client_t *clients, struct pollfd *fds)
{
    char **args = get_client_command(fds[client_index].fd);

    if (args == NULL) {
        return ftp_response(fds[client_index].fd, FTP_INVALID_CMD);
    } else if (strcmp(args[0], "QUIT") == 0 || strcmp(args[0], "quit") == 0) {
        disconnect_client(client_index, clients, fds);
    } else if (strcmp(args[0], "USER") == 0 || strcmp(args[0], "user") == 0) {
        user_command(client_index, clients, fds, args);
    } else if (strcmp(args[0], "PASS") == 0 || strcmp(args[0], "pass") == 0) {
        pass_command(client_index, clients, fds, args);
    } else if (strcmp(args[0], "PWD") == 0 || strcmp(args[0], "pwd") == 0) {
            pwd_command(client_index, clients, fds);
    } else if (strcmp(args[0], "HELP") == 0 || strcmp(args[0], "help") == 0) {
            help_command(client_index, fds);
    } else {
        printf("Received command from client %d: '%s'\n",
            fds[client_index].fd, args[0]);
        print_command_args(args);
    }
    free_args(args);
}
