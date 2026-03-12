/*
** EPITECH PROJECT, 2024
** Project
** File description:
** pasv command
*/

#include "client.h"

int check_pasv_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args)
{
    if (!clients[client_index].is_logged) {
        ftp_response(fds[client_index].fd, FTP_NOT_LOGGED_IN);
        return -1;
    }
    return 0;
}

int init_data_socket(int *data_fd, int port)
{
    struct sockaddr_in data_address;

    *data_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (*data_fd == -1)
        return return_error("Failed to create data socket", -1);
    data_address.sin_family = AF_INET;
    data_address.sin_addr.s_addr = INADDR_ANY;
    data_address.sin_port = htons(port);
    if (bind(*data_fd, (struct sockaddr *)&data_address, sizeof(data_address)) == -1) {
        close(*data_fd);
        return return_error("Failed to bind data socket", -1);
    }
    if (listen(*data_fd, 1) == -1) {
        close(*data_fd);
        return return_error("Failed to listen on data socket", -1);
    }
    return 0;
}


void pasv_command(int client_index, client_t *clients, struct pollfd *fds,
    char **args)
{
    (void)args;
    if (check_pasv_command(client_index, clients, fds, args) == -1)
        return;
    if (init_data_socket(&clients[client_index].data_fd, 0) == -1)
        return;

    uint16_t port = get_pasv_port(clients[client_index].data_fd);
    
    int port1 = 0;
    int port2 = 0;
    int data_port = port1 * 256 + port2;
    init_data_socket(&clients[client_index].data_fd, data_port);
    clients[client_index].state = PASSIVE;
    printf("Passive data socket initialized on port %d\n", data_port);
    dprintf(fds[client_index].fd, "227 Entering Passive Mode (127,0,0,1,%d,%d)\r\n", port1, port2);
}
