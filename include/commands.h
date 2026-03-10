/*
** EPITECH PROJECT, 2023
** include
** File description:
** commands.h
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

#ifndef COMMANDS_H
    #define COMMANDS_H

    #include "my.h"
    #include "error_handling.h"
    #include "client.h"
    #include "server.h"
    #include "constant.h"

struct commands_s {
    const char *name;
    void (*command)(int client_index, client_t *clients, struct pollfd *fds,
        char **args);
};

void handle_commands(int client_index, client_t *clients, struct pollfd *fds);
char **parse_command(const char *command);
void print_command_args(char **args);
void free_args(char **args);
char **get_client_command(int client_fd);
int verify_auth(int client_index, client_t *clients, struct pollfd *fds);

void user_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args);
void pass_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args);
void pwd_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args);
void help_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args);
void noop_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args);

#endif /* COMMANDS_H */
