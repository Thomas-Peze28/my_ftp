/*
** EPITECH PROJECT, 2024
** Project
** File description:
** handle_client
*/

#include "commands.h"

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
        return;
    } else if (strcmp(args[0], "QUIT") == 0 || strcmp(args[0], "quit") == 0) {
        disconnect_client(client_index, clients, fds);
    } else {
        printf("Received command from client %d: '%s'\n", fds[client_index].fd, args[0]);
        print_command_args(args);
    }
    free_args(args);
}
