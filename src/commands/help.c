/*
** EPITECH PROJECT, 2024
** Project
** File description:
** help command
*/

#include "server.h"

void help_command(server_t *server, int client_index, char **args)
{
    (void)args;
    ftp_response(server->fds[client_index].fd,
        "214-The following commands are supported:\r\n"
        "USER PASS PWD QUIT HELP NOOP CWD CDUP DELE\r\n"
        "214 End of HELP info\r\n");
}
