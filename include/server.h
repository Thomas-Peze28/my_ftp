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

int init_server(int port);

#endif /* SERVER_H */
