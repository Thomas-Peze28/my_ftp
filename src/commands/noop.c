/*
** EPITECH PROJECT, 2024
** Project
** File description:
** noop command
*/

#include "client.h"

void noop_command(int client_index, struct pollfd *fds)
{
    ftp_response(fds[client_index].fd, "200 NOOP command successful\r\n");
}