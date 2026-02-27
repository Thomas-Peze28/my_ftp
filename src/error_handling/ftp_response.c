/*
** EPITECH PROJECT, 2024
** Project
** File description:
** ftp_response
*/

#include "constant.h"
#include <unistd.h>
#include <stdio.h>

void ftp_response(int client_fd, const char *message)
{
    dprintf(client_fd, "%s", message);
}
