/*
** EPITECH PROJECT, 2024
** Project
** File description:
** is_valid_home
*/

#include "myftp.h"
#include <dirent.h>

bool is_valid_home(const char *path)
{
    DIR *dir;

    if (path == NULL || strlen(path) == 0) {
        return false;
    }
    
    dir = opendir(path);
    if (dir == NULL) {
        return false;
    }
    closedir(dir);
    return true;
}