/*
** EPITECH PROJECT, 2023
** include
** File description:
** client.h
*/

#include "my.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <poll.h>

#ifndef CLIENT_H
    #define CLIENT_H

    #include "constant.h"
    #include "error_handling.h"

typedef struct client_s {
    int fd;
    char *username;
    char *path;
    bool is_logged;
} client_t;

void init_clients(client_t *clients, struct pollfd *fds, char *path);
int accept_new_connection(int server_fd, client_t *clients,
    struct pollfd *fds);
void disconnect_client(int index, client_t *clients, struct pollfd *fds);

int connection(int socket_fd, struct sockaddr_in *client_address,
    socklen_t client_address_len);
int response(int accept_result);

#endif /* CLIENT_H */
