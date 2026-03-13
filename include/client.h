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

typedef enum data_state {
    INACTIVE,
    PASSIVE,
    ACTIVE
} data_state;

typedef struct client_s {
    int fd;
    int data_fd;
    data_state state;
    char *username;
    char *current_dir;
    bool is_logged;
} client_t;

#endif /* CLIENT_H */
