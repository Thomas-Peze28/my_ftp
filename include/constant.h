/*
** EPITECH PROJECT, 2023
** include
** File description:
** constant.h
*/

#ifndef CONSTANT_H
    #define CONSTANT_H

    #define MAX_CLIENTS 1023

    #define FTP_WELCOME "220 Welcome to my FTP server!\r\n"
    #define FTP_GOODBYE "221 Goodbye!\r\n"
    #define FTP_USER_OK "331 Username OK, need password\r\n"
    #define FTP_LOGIN_OK "230 User logged in\r\n"
    #define FTP_ALREADY_LOGIN "503 Already logged in\r\n"
    #define FTP_BAD_SEQUENCE "503 Bad sequence\r\n"
    #define FTP_REAUTH_FAIL "501 Reauthentication not supported\r\n"
    #define FTP_INVALID_CMD "500 Invalid command: Try to be more creative\r\n"
    #define FTP_UNKNOW_CMD "500 Unknown command\r\n"
    #define FTP_NEED_USER "500 Invalid command: Username is required\r\n"
    #define FTP_NEED_PASS "500 Invalid command: Password is required\r\n"
    #define FTP_NOT_LOGGED_IN "530 Please login with USER and PASS\r\n"
    #define FTP_NOT_PASSED "530 Not logged in: Password required\r\n"
    #define FTP_BAD_LOGIN "530 Not logged in: Incorrect password\r\n"
    #define FTP_MAX_CLIENT "421 Service not available\r\n"
    #define FTP_NEED_ARG "501 Invalid number of parameters\r\n"
    #define FTP_DIR_CHANGED "250 Directory successfully changed\r\n"
    #define FTP_DIR_CHANGE_FAIL "550 Failed to change directory\r\n"
    #define FTP_OUT_OF_ROOT "550 You try to escape the root directory !\r\n"
    #define FTP_FILE_DELETED "250 File successfully deleted\r\n"
    #define FTP_FILE_DELETE_FAIL "550 Failed to delete file\r\n"
    #define FTP_DATA_CONNECTION "425 Can't open data connection\r\n"
    #define FTP_FILE_UNAVAILABLE "550 File unavailable\r\n"
    #define FTP_FILE_STATUS "150 File status okay\r\n"
    #define FTP_DIR_SEND_OK "226 Directory send OK\r\n"

    #define PATH_MAX 4096

    #define HOME server->home_dir

void ftp_response(int client_fd, const char *message);

#endif /* CONSTANT_H */
