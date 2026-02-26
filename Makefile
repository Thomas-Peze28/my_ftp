##
## EPITECH PROJECT, 2026
## makefile
## File description:
## project
##

SERVER	=	src/server/init_server.c	\

CLIENT	=	src/client/init_clients.c	\
			src/client/connect_client.c	\
			src/client/disconnect_client.c	\

COMMANDS	=	src/commands/handle_commands.c	\

ERRORS_HANDLING	=	src/error_handling/is_valid_home.c	\
					src/error_handling/is_valid_port.c	\
					src/error_handling/print_help.c	\
					src/error_handling/handle_errors.c	\
					src/error_handling/return_error.c	\

SRC	=	src/main.c	\
		$(SERVER)	\
		$(CLIENT)	\
		$(COMMANDS)	\
		$(ERRORS_HANDLING)	\

OBJ	=	$(SRC:.c=.o)

NAME	=	myftp

CFLAGS = -Wextra -Wall -I ./include/ -lm -std=gnu17

all:	$(NAME)

$(NAME):	$(OBJ)
	epiclang -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all
