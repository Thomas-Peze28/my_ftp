/*
** EPITECH PROJECT, 2024
** Project
** File description:
** handle_errors
*/

#include "myftp.h"

bool handle_errors(int argc, char **argv)
{
    if (argc != 3) {
        print_help();
        return true;
    }
    if (!is_valid_port(argv[1])) {
        printf("Invalid port number\n");
        return true;
    }
    if (!is_valid_home(argv[2])) {
        printf("Invalid home directory\n");
        return true;
    }
    return false;
}