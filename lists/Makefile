##
## Makefile for c_lists in /home/mart_i/Work/unix/irc-mart_i-magere_n/c_lists/
## 
## Made by pierre martin
## Login   <mart_i@epitech.net>
## 
## Started on  Wed Apr 18 00:12:20 2012 pierre martin
## Last update Tue Jun 12 16:52:51 2012 pierre martin
##

NAME	=	libclists.a

SRC_BASE=	base/alloc_base.c	\
		base/init_base.c	\
		base/desalloc.c

SRC_LIST=	lists_ops/alloc.c	\
		lists_ops/add.c		\
		lists_ops/add_new.c	\
		lists_ops/add_ctor.c	\
		lists_ops/add_copy.c	\
		lists_ops/remove.c	\
		lists_ops/getor.c	\
		lists_algo/features.c	\
		lists_algo/sort.c	\
		lists_algo/partI.c

SRC_WRAP=	wrapper/pqueue.c	\
		wrapper/pqueue_tools.c

OBJ	=	$(SRC_BASE:.c=.o)	\
		$(SRC_LIST:.c=.o)	\
		$(SRC_WRAP:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -O3 -I ./include

GCC	=	gcc

RM	=	rm -rf
DUST	=	./*~ lists_ops/*~ base/*~ include/*~

%.o: 		%.c
		$(GCC) $(CFLAGS) -o $@ -c $<

all:		$(NAME)

$(NAME):	$(OBJ) do_lib

debug:		CFLAGS = -Wall -Werror -g -I./include
debug:		fclean $(OBJ) do_lib

do_lib:
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

clean:
		@$(RM) $(OBJ)
		@$(RM) $(DUST)

fclean:		clean
		@$(RM) $(NAME)

re:		fclean all
