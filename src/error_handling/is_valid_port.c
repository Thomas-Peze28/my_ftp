/*
** EPITECH PROJECT, 2024
** Project
** File description:
** is_valid_port
*/

#include "myftp.h"

bool is_valid_port(const char *port_str)
{
    int port = 0;

    if (port_str == NULL) {
        return false;
    }
    port = atoi(port_str);
    if (port < 0 || port > 65535) {
        return false;
    }
    return true;
}