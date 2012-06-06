##
## Fiahil
## 06.06.2012
##

NAME	=	zappy

SRC	=	src/main.c		\
		src/cmd_parse.c		\
		src/string_manager.c

OBJ	=	$(SRC:.c=.o)

INCLUDES=	-I ./headers

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

