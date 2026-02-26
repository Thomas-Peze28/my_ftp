/*
** EPITECH PROJECT, 2024
** Project
** File description:
** handle_client
*/

#include "commands.h"

char *get_client_command(int client_fd)
{
    char buffer[1024];
    int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);

    if (strcmp(buffer, "\r\n") == 0 || strcmp(buffer, "\n") == 0)
        return NULL;
    if (bytes_read > 0) {
        if (bytes_read > 1 && buffer[bytes_read - 1] == '\n' && buffer[bytes_read - 2] == '\r')
            buffer[bytes_read - 2] = '\0';
        else
            buffer[bytes_read] = '\0';
        return strdup(buffer);
    }
    return NULL;
}

void handle_commands(int client_index, client_t *clients, struct pollfd *fds)
{
    char *command = get_client_command(fds[client_index].fd);

    if (command == NULL) {
        return;
    } else if (strcmp(command, "QUIT") == 0 || strcmp(command, "quit") == 0) {
        disconnect_client(client_index, clients, fds);
    } else {
        printf("Received command from client %d: '%s'\n", fds[client_index].fd, command);
    }
    free(command);
    command = NULL;
}
