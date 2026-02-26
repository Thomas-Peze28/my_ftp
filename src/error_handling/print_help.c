/*
** EPITECH PROJECT, 2024
** Project
** File description:
** print_help
*/

#include "myftp.h"
#include <dirent.h>

int print_help(void)
{
    printf("Usage: ./myftp [PORT] [HOME]\n");
    printf("PORT: The port number to listen on (0-65535)\n");
    printf("HOME: The home directory for the FTP server\n");
    return 0;
}
