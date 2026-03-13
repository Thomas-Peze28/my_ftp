/*
** EPITECH PROJECT, 2024
** Project
** File description:
** get_socket_ip
*/

#include "server.h"

unsigned char *get_socket_ip(int socket_fd)
{
    struct sockaddr_in address;
    socklen_t address_len = sizeof(address);
    unsigned char *ip = malloc(4);

    if (getsockname(socket_fd,
        (struct sockaddr *)&address, &address_len) == -1) {
        free(ip);
        return NULL;
    }
    memcpy(ip, &address.sin_addr.s_addr, 4);
    return ip;
}
