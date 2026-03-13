/*
** EPITECH PROJECT, 2024
** Project
** File description:
** init_data_socket
*/

#include "server.h"

int check_data_socket(int *data_fd, struct sockaddr_in *data_address)
{
    if (bind(*data_fd,
        (struct sockaddr *)data_address, sizeof(*data_address)) == -1) {
        close(*data_fd);
        return return_error("Failed to bind data socket", -1);
    }
    if (listen(*data_fd, 1) == -1) {
        close(*data_fd);
        return return_error("Failed to listen on data socket", -1);
    }
    return 0;
}

int init_data_socket(int *data_fd, int port)
{
    struct sockaddr_in data_address;
    int data_port = 0;

    *data_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (*data_fd == -1)
        return return_error("Failed to create data socket", -1);
    data_address.sin_family = AF_INET;
    data_address.sin_addr.s_addr = INADDR_ANY;
    data_address.sin_port = htons(port);
    if (check_data_socket(data_fd, &data_address) == -1)
        return -1;
    getsockname(*data_fd,
        (struct sockaddr *)&data_address, &(socklen_t){sizeof(data_address)});
    data_port = ntohs(data_address.sin_port);
    return data_port;
}
