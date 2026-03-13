/*
** EPITECH PROJECT, 2023
** include
** File description:
** myftp.h
*/

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

    #include "my.h"
    #include "error_handling.h"
    #include "client.h"
    #include "server.h"
    #include "commands.h"
    #include "constant.h"

int myftp(int port, char *path);

#endif /* MYFTP_H */
