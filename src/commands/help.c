/*
** EPITECH PROJECT, 2024
** Project
** File description:
** help command
*/

#include "client.h"

void help_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args)
{
    (void)clients;
    (void)args;
    ftp_response(fds[client_index].fd,
        "214-The following commands are supported:\r\n"
        "USER PASS PWD QUIT HELP NOOP CWD\r\n"
        "214 End of HELP info\r\n");
}
