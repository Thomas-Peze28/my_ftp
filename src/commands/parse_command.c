/*
** EPITECH PROJECT, 2024
** Project
** File description:
** parse_command
*/

#include "commands.h"

int count_args(const char *command)
{
    int count = 0;
    char *token = NULL;
    char *command_copy = strdup(command);

    token = strtok(command_copy, " \t\r\n");
    while (token != NULL) {
        count++;
        token = strtok(NULL, " \t\r\n");
    }
    free(command_copy);
    return count;
}

char **parse_command(const char *command)
{
    int arg_count = count_args(command);
    char **args = NULL;
    char *token = NULL;
    char *command_copy = NULL;
    int index = 0;

    if (arg_count == 0)
        return NULL;
    args = malloc(sizeof(char *) * (arg_count + 1));
    command_copy = strdup(command);
    token = strtok(command_copy, " \t\r\n");
    while (token != NULL && index < arg_count) {
        args[index] = strdup(token);
        token = strtok(NULL, " \t\r\n");
        index++;
    }
    args[index] = NULL;
    free(command_copy);
    return args;
}

void print_command_args(char **args)
{
    for (int i = 0; args[i] != NULL; i++) {
        printf("Argument %d: '%s'\n", i + 1, args[i]);
    }
}

void free_args(char **args)
{
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}
