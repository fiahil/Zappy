NAME	=	server

SRC	=	main.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -O3

CC	=	gcc

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean:
		rm -rfv *~ *# $(OBJ)

fclean:		clean
		rm -rfv $(NAME)

re:		fclean all