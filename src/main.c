/*
** EPITECH PROJECT, 2024
** Project
** File description:
** main
*/

#include "myftp.h"

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
        if (fds[0].revents & POLLIN)
            accept_new_connection(socket_fd, clients, fds);
        for (int i = 1; i < MAX_CLIENTS; i++) {
            if (fds[i].fd != -1 && (fds[i].revents & POLLIN))
                handle_commands(i, clients, fds);
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
