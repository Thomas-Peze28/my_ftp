/*
** EPITECH PROJECT, 2023
** include
** File description:
** myftp.h
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

#ifndef MYFTP_H
    #define MYFTP_H

    bool is_valid_port(const char *port);
    bool is_valid_home(const char *path);
    int print_help(void);

#endif /* MYFTP_H */
