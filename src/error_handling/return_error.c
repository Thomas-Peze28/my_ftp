/*
** EPITECH PROJECT, 2024
** Project
** File description:
** return_error
*/

#include "myftp.h"

int return_error(const char *message, int return_code)
{
    printf("%s\n", message);
    return return_code;
}