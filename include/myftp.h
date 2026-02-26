/*
** EPITECH PROJECT, 2023
** include
** File description:
** myftp.h
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

#ifndef MYFTP_H
    #define MYFTP_H

    int init_server(int port);
    int connection(int socket_fd, struct sockaddr_in client_address, socklen_t client_address_len);
    int response(int accept_result);
    int myftp(int port, char *path);

#endif /* MYFTP_H */
