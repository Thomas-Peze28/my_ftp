/*
** EPITECH PROJECT, 2024
** Project
** File description:
** handle_client
*/

#include "commands.h"

const struct commands_s command_list[] = {
    {"USER", user_command},
    {"PASS", pass_command},
    {"PWD", pwd_command},
    {"HELP", help_command},
    {"NOOP", noop_command},
    {"CWD", cwd_command},
    {"QUIT", quit_command},
    {"CDUP", cdup_command},
    {NULL, NULL}
};

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

    for (int i = 0; command_list[i].name != NULL; i++) {
        if (strcmp(args[0], command_list[i].name) == 0) {
            command_list[i].command(client_index, clients, fds, args);
            free_args(args);
            return;
        }
    }
    ftp_response(fds[client_index].fd, FTP_UNKNOW_CMD);
    free_args(args);
}
