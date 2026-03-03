/*
** EPITECH PROJECT, 2024
** Project
** File description:
** help command
*/

#include "client.h"

void help_command(int client_index, struct pollfd *fds)
{
    char *help_message =
        "214-The following commands are supported:\r\n"
        "USER PASS PWD QUIT HELP\r\n"
        "214 End of HELP info\r\n";
    ftp_response(fds[client_index].fd, help_message);
}
