/*
** EPITECH PROJECT, 2023
** include
** File description:
** server.h
*/

#include "my.h"
#include "error_handling.h"

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

#ifndef SERVER_H
    #define SERVER_H

    #include "constant.h"
    #include "client.h"

typedef struct server_s {
    int port;
    int socket_fd;
    int current_clients;
    client_t clients[MAX_CLIENTS];
    struct pollfd fds[MAX_CLIENTS];
    char *home_dir;
} server_t;

int init_server(server_t *server, int port);
void init_clients(server_t *server, char *path);
int accept_new_connection(server_t *server, char *path);
void disconnect_client(server_t *server, int index);
int init_data_socket(int *data_fd, int port);
unsigned char *get_socket_ip(int socket_fd);
int check_data_sock(server_t *server, int client_index, int data_sock,
    char *path);
int check_path_error(server_t *server, int client_index, char *path);

#endif /* SERVER_H */
