/*
** EPITECH PROJECT, 2023
** include
** File description:
** constant.h
*/

#ifndef CONSTANT_H
    #define CONSTANT_H

    #define MAX_CLIENTS 50000

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

void ftp_response(int client_fd, const char *message);

#endif /* CONSTANT_H */
