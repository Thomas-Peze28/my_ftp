/*
** EPITECH PROJECT, 2024
** Project
** File description:
** pasv command
*/

#include "server.h"

void check_state(server_t *server, int client_index)
{
    if (server->clients[client_index].state == ACTIVE ||
        server->clients[client_index].state == PASSIVE ||
        server->clients[client_index].data_fd != -1) {
        close(server->clients[client_index].data_fd);
        server->clients[client_index].data_fd = -1;
        server->clients[client_index].state = INACTIVE;
    }
    return;
}

int check_pasv_command(server_t *server, int client_index, char **args)
{
    if (!server->clients[client_index].is_logged) {
        ftp_response(server->fds[client_index].fd, FTP_NOT_LOGGED_IN);
        return -1;
    }
    if (args[1] != NULL) {
        ftp_response(server->fds[client_index].fd, FTP_NEED_ARG);
        return -1;
    }
    return 0;
}

int check_ip(server_t *server, int client_index, unsigned char *ip)
{
    if (ip == NULL) {
        close(server->clients[client_index].data_fd);
        server->clients[client_index].data_fd = -1;
        ftp_response(server->fds[client_index].fd, FTP_DATA_CONNECTION);
        return -1;
    }
    return 0;
}

void print_pasv_info(server_t *server, unsigned char *ip, int *ports,
    int client_index)
{
    printf("Passive data socket initialized on port %d for client %d\n",
        ports[0] * 256 + ports[1], client_index);
    dprintf(server->fds[client_index].fd,
        "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)\r\n",
        ip[0], ip[1], ip[2], ip[3], ports[0], ports[1]);
}

void pasv_command(server_t *server, int client_index, char **args)
{
    int data_port = 0;
    int port1 = 0;
    int port2 = 0;
    unsigned char *ip = NULL;

    if (check_pasv_command(server, client_index, args) == -1)
        return;
    check_state(server, client_index);
    data_port = init_data_socket(&server->clients[client_index].data_fd, 0);
    if (data_port == -1)
        return ftp_response(server->fds[client_index].fd, FTP_DATA_CONNECTION);
    port1 = data_port / 256;
    port2 = data_port % 256;
    ip = get_socket_ip(server->socket_fd);
    if (check_ip(server, client_index, ip) == -1)
        return;
    server->clients[client_index].state = PASSIVE;
    print_pasv_info(server, ip, (int[]){port1, port2}, client_index);
    free(ip);
}
