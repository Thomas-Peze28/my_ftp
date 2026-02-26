/*
** EPITECH PROJECT, 2023
** include
** File description:
** error_handling.h
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef ERR_H
    #define ERR_H

    bool is_valid_port(const char *port);
    bool is_valid_home(const char *path);
    int print_help(void);
    int return_error(const char *message, int return_code);
    bool handle_errors(int argc, char **argv);

#endif /* ERR_H */
