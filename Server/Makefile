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
		src/get_opt_3.c			\
		src/usage.c			\
		src/parse_arg.c			\
		src/var_manager.c		\
		src/select_manager.c		\
		src/select_tools.c		\
		src/max_fd.c			\
		src/func_cmp.c			\
		src/server_routine.c		\
		src/cmd_parse.c			\
		src/my_itoa.c			\
		src/map.c			\
		src/clock.c			\
		src/func_cleaner.c		\
		src/process_function_1.c	\
		src/process_function_2.c	\
		src/process_function_3.c	\
		src/msgout_cmd_1.c		\
		src/msgout_cmd_2.c		\
		src/msgout_cmd_3.c		\
		src/team_manager.c		\
		src/string_manager.c		\
		src/egg_manager.c		\
		src/network.c			\
		src/my_send.c			\
		src/my_receive.c		\
		src/handle_error.c		\
		src/vision_tab.c		\
		src/welcome_player.c		\
		src/iter.c			\
		src/iter_function.c		\
		src/iter_tools.c		\
		src/set_timeout.c		\
		src/fill_map.c			\
		src/broadcast.c			\
		src/graphic_tools.c		\
		src/graphic_function_1.c	\
		src/graphic_function_2.c	\
		src/graphic_function_4.c	\
		src/graphic_function_5.c	\
		src/incantation_manager.c	\
		src/player.c

OBJ	=	$(SRC:.c=.o)

INCLUDES=	-I ./headers -I ./lists/include

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -g $(INCLUDES)

LDFLAGS	=	-L./lists/ -lclists -lm

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

liblist:
		@$(MAKE) all -C ./lists
		@$(MAKE) clean -C ./lists

clean:
		@$(RM) $(OBJ)

fclean:		clean
		@$(RM) $(NAME)

re:		fclean all

