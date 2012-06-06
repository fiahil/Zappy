##
## Fiahil
## 06.06.2012
##

NAME	=	zappy

SRC	=	src/main.c		\
		src/get_arg.c		\
		src/get_opt_1.c		\
		src/get_opt_2.c		\
		src/usage.c		\
		src/cmd_parse.c		\
		src/string_manager.c	\
		src/network.c		\
		src/error.c		\
		src/netManager.c

OBJ	=	$(SRC:.c=.o)

INCLUDES=	-I ./headers -I ./lists/include

CC	=	gcc

CFLAGS	=	-Wall -Wextra -O3 $(INCLUDES)

LDFLAGS	=

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

