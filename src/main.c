/*
** EPITECH PROJECT, 2024
** Project
** File description:
** main
*/

#include "myftp.h"

int connection(int socket_fd, struct sockaddr_in *client_address, socklen_t client_address_len)
{
    int accept_result = accept(socket_fd, (struct sockaddr *)client_address, &client_address_len);

    if (accept_result == -1) {
        printf("Failed to accept connection\n");
        return 84;
    } else {
        printf("Connection from %s:%d\n", inet_ntoa(client_address->sin_addr), ntohs(client_address->sin_port));
    }
    return accept_result;
}

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

int myftp(int port, int socket_fd, char *path)
{
    struct pollfd fds[MAX_CLIENTS];
    client_t clients[MAX_CLIENTS];
    int poll_result = 0;
    (void)path;

    init_clients(clients, fds);
    fds[0].fd = socket_fd;
    fds[0].events = POLLIN;
    printf("Server is listening on port %d\n", port);
    while (1) {
        poll_result = poll(fds, MAX_CLIENTS, -1);

        if (poll_result == -1) {
            printf("Failed to poll\n");
            break;
        }
        if (fds[0].revents & POLLIN) {
            accept_new_connection(socket_fd, clients, fds);
        }
        for (int i = 1; i < MAX_CLIENTS; i++) {
            if (fds[i].fd != -1 && (fds[i].revents & POLLIN)) {

                char *command = get_client_command(fds[i].fd);

                if (command == NULL) {
                    printf("Client %d disconnected.\n", fds[i].fd);
                    close(fds[i].fd);
                    fds[i].fd = -1;
                } else if (strcmp(command, "QUIT") == 0 || strcmp(command, "quit") == 0) {
                    disconnect_client(i, clients, fds);
                    free(command);
                    continue;
                } else {
                    printf("Received command from client %d: '%s'\n", fds[i].fd, command);
                    free(command);
                }
            }
        }
    }
    close(socket_fd);
    return 0;
}

int main(int argc, char **argv)
{
    int port = 0;
    int socket_fd = 0;

    if (handle_errors(argc, argv))
        return 84;
    port = atoi(argv[1]);
    socket_fd = init_server(port);
    if (socket_fd == -1)
        return 84;
    myftp(port, socket_fd, argv[2]);
    return 0;
}
