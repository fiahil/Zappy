##
## Fiahil
## 06.06.2012
##

NAME	=	zappy

MAKE=           make --no-print-directory

SRC	=	src/main.c		\
		src/get_arg.c		\
		src/get_opt_1.c		\
		src/get_opt_2.c		\
		src/usage.c		\
		src/select_manager.c	\
		src/max_fd.c		\
		src/server_routine.c	\
		src/cmd_parse.c		\
		src/string_manager.c	\
		src/network.c		\
		src/handle_error.c	\
		src/netManager.c

OBJ	=	$(SRC:.c=.o)

INCLUDES=	-I ./headers -I ./lists/include

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -g $(INCLUDES)

LDFLAGS	=	-L./lists/ -lclists

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

list:
		@$(MAKE) all -C ./lists
		@$(MAKE) clean -C ./lists

clean:
		@$(RM) $(OBJ)

fclean:		clean
		@$(RM) $(NAME)

re:		fclean all

