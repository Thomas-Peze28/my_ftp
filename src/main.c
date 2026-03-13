/*
** EPITECH PROJECT, 2024
** Project
** File description:
** main
*/

#include "myftp.h"
#include <signal.h>

void update_event_loop(server_t *server)
{
    for (int i = 1; i < MAX_CLIENTS; i++) {
        if (server->fds[i].fd != -1 && (server->fds[i].revents & POLLIN))
            handle_commands(server, i);
    }
}

int myftp(int port, char *path)
{
    server_t server;
    int poll_result = 0;

    if (init_server(&server, port) == -1)
        return 84;
    init_clients(&server, path);
    while (1) {
        poll_result = poll(server.fds, MAX_CLIENTS, -1);
        if (poll_result == -1) {
            printf("Failed to poll\n");
            break;
        }
        if (server.fds[0].revents & POLLIN)
            accept_new_connection(&server, path);
        update_event_loop(&server);
    }
    close(server.socket_fd);
    free(server.home_dir);
    return 0;
}

int main(int argc, char **argv)
{
    if (handle_errors(argc, argv))
        return 84;
    return myftp(atoi(argv[1]), argv[2]);
}
