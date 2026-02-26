/*
** EPITECH PROJECT, 2024
** Project
** File description:
** main
*/

#include "myftp.h"

#define MAX_CLIENTS 100

int connection(int socket_fd, struct sockaddr_in client_address, socklen_t client_address_len)
{
    int accept_result = accept(socket_fd, (struct sockaddr *)&client_address, &client_address_len);

    if (accept_result == -1) {
        printf("Failed to accept connection\n");
        return 84;
    } else {
        printf("Connection from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
    }
    return accept_result;
}

int welcome(int accept_result)
{
    char *msg = "Welcome to MyFTP!\n";
    write(accept_result, msg, strlen(msg));
    return 0;
}

int goodbye(int accept_result)
{
    write(accept_result, "Goodbye Client!\n", strlen("Goodbye Client!\n"));
    close(accept_result);
    return 0;
}

int init_server(int port)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;

    if (socket_fd == -1)
        return return_error("Failed to create socket", -1);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        close(socket_fd);
        return return_error("Failed to bind socket", -1);
    }
    if (listen(socket_fd, MAX_CLIENTS) == -1)
    {
        close(socket_fd);
        return return_error("Failed to listen on socket", -1);
    }
    return socket_fd;
}

struct pollfd *init_pollfd(int socket_fd)
{
    struct pollfd *fds = malloc(MAX_CLIENTS * sizeof(struct pollfd));

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        fds[i].fd = -1;
        fds[i].events = POLLIN;
    }
    fds[0].fd = socket_fd;
    fds[0].events = POLLIN;
    return fds;
}

char *get_client_command(int client_fd)
{
    char buffer[1024];
    int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);

    if (strcmp(buffer, "\r\n") == 0 || strcmp(buffer, "\n") == 0)
        return NULL;
    if (bytes_read > 0) {
        if (bytes_read > 1 && buffer[bytes_read - 1] == '\n' && buffer[bytes_read - 2] == '\r')
            buffer[bytes_read - 2] = '\0';
        else
            buffer[bytes_read] = '\0';
        return strdup(buffer);
    }
    return NULL;
}

int myftp(int port, char *path)
{
    int socket_fd = init_server(port);
    int poll_result = 0;

    if (socket_fd == -1)
        return 84;

    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
    int accept_result = 0;

    struct pollfd *fds = init_pollfd(socket_fd);

    while (1)
    {
        poll_result = poll(fds, MAX_CLIENTS, -1);

        if (poll_result == -1) {
            printf("Failed to poll\n");
            break;
        }
        if (fds[0].revents & POLLIN) {
            accept_result = connection(socket_fd, client_address, client_address_len);
            if (accept_result != -1 && accept_result < MAX_CLIENTS) {
                fds[accept_result].fd = accept_result;
                fds[accept_result].events = POLLIN;
                welcome(accept_result);
            }
        }
        for (int i = 1; i < MAX_CLIENTS; i++) {
            if (fds[i].fd != -1 && (fds[i].revents & POLLIN)) {

                char *command = get_client_command(fds[i].fd);

                if (command == NULL) {
                    printf("Client %d disconnected.\n", fds[i].fd);
                    close(fds[i].fd);
                    fds[i].fd = -1;
                } else if (strcmp(command, "QUIT") == 0 || strcmp(command, "quit") == 0) {
                    printf("Client %d sent QUIT command. Closing connection.\n", fds[i].fd);
                    goodbye(fds[i].fd);
                    fds[i].fd = -1;
                    free(command);
                    continue;
                } else {
                    printf("Received command from client %d: '%s'\n", fds[i].fd, command);
                    free(command);
                }
            }
        }
    }
    free(fds);
    close(socket_fd);
    return 0;
}

int main(int argc, char **argv)
{
    int port = 0;

    if (handle_errors(argc, argv))
        return 84;
    port = atoi(argv[1]);
    myftp(port, argv[2]);
    return 0;
}
