##
## Makefile
##
## Fiahil
## Fri May  4 2012

NAME	=	parser

SRC	=	parser.tab.c		\
		lex.yy.c		\
		main.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -O3

CC	=	gcc

%.o: %.c
	$(CC) -o $@	-c $<	$(CFLAGS)

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:		clean
	rm -f $(NAME)

autoclean:	fclean
	rm -f parser.tab.h parser.tab.c lex.yy.c lex.yy.h

re:		fclean all

regen:		autoclean all

lex.yy.o:	lex.yy.c
	$(CC) -o $@	-c $<	$(CFLAGS)

parser.tab.o:	parser.tab.c
	$(CC) -o $@	-c $<	$(CFLAGS)

lex.yy.c:	scanner.l parser.tab.c
	flex -o lex.yy.c scanner.l

parser.tab.c:	parser.y
	bison parser.y -d

