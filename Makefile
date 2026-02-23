##
## EPITECH PROJECT, 2026
## makefile
## File description:
## project
##

ERRORS_HANDLING	=	src/error_handling/is_valid_home.c	\
					src/error_handling/is_valid_port.c	\
					src/error_handling/print_help.c	\
					src/error_handling/handle_errors.c	\

SRC	=	src/main.c	\
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
