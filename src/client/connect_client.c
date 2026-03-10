/*
** EPITECH PROJECT, 2024
** Project
** File description:
** connect_client
*/

#include "client.h"

int is_available_slot(struct pollfd *fds)
{
    for (int i = 1; i < MAX_CLIENTS; i++) {
        if (fds[i].fd == -1)
            return i;
    }
    return -1;
}

void fill_client_info(client_t *client, int fd, char *path)
{
    char real_path[4096];

    client->fd = fd;
    client->is_logged = false;
    client->username = NULL;
    
    if (realpath(path, real_path) != NULL) {
        client->home_dir = strdup(real_path);
        client->current_dir = strdup(real_path);
    } else {
        client->home_dir = strdup(path);
        client->current_dir = strdup(path);
    }
}

int accept_new_connection(int server_fd, client_t *clients, struct pollfd *fds,
    char *path)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int new_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    int slot = -1;

    if (new_fd < 0)
        return return_error("Failed to accept new connection", -1);
    slot = is_available_slot(fds);
    if (slot == -1) {
        ftp_response(new_fd, FTP_MAX_CLIENT);
        close(new_fd);
        return return_error("No available slot for new client", -1);
    }
    fds[slot].fd = new_fd;
    fds[slot].events = POLLIN;
    fill_client_info(&clients[slot], new_fd, path);
    printf("Client connected on slot %d (fd: %d)\n", slot, new_fd);
    ftp_response(new_fd, FTP_WELCOME);
    return new_fd;
}
