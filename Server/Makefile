##
## Fiahil
## 06.06.2012
##

NAME	=	zappy

MAKE=           make --no-print-directory

SRC	=	src/main.c			\
		src/get_arg.c			\
		src/get_opt_1.c			\
		src/get_opt_2.c			\
		src/usage.c			\
		src/epoll_manager.c		\
		src/max_fd.c			\
		src/server_routine.c		\
		src/cmd_parse.c			\
		src/my_itoa.c			\
		src/map.c			\
		src/clock.c			\
		src/process_function.c		\
		src/process_function2.c		\
		src/process_function3.c		\
		src/string_manager.c		\
		src/network.c			\
		src/my_send.c			\
		src/my_receive.c		\
		src/handle_error.c		\
		src/protocol.c			\
		src/netManager.c		\
		src/fill_map.c

OBJ	=	$(SRC:.c=.o)

INCLUDES=	-I ./headers -I ./lists/include

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -g $(INCLUDES)

LDFLAGS	=	-L./lists/ -lclists

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

lists:
		@$(MAKE) all -C ./lists
		@$(MAKE) clean -C ./lists

clean:
		@$(RM) $(OBJ)

fclean:		clean
		@$(RM) $(NAME)

re:		fclean all
