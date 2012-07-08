##
## Makefile for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
## 
## Made by ulric lefevre
## Login   <lefevr_u@epitech.net>
## 
## Started on  Tue Jul  3 13:29:53 2012 ulric lefevre
## Last update Sun Jul  8 20:13:36 2012 ulric lefevre
##

NAME	=	zappy

MAKE	=       make --no-print-directory

SRC	=	src/broadcast.c			\
		src/clock.c			\
		src/cmd_parse.c			\
		src/egg_manager.c		\
		src/fill_map.c			\
		src/func_cleaner_1.c		\
		src/func_cleaner_2.c		\
		src/func_cmp.c			\
		src/func_ctor_dtor_1.c		\
		src/func_ctor_dtor_2.c		\
		src/get_arg.c			\
		src/get_opt_1.c			\
		src/get_opt_2.c			\
		src/get_opt_3.c			\
		src/graphic_function_1.c	\
		src/graphic_function_2.c	\
		src/graphic_function_3.c	\
		src/graphic_function_4.c	\
		src/graphic_function_5.c	\
		src/graphic_function_6.c	\
		src/graphic_function_all.c	\
		src/graphic_process_1.c		\
		src/graphic_process_2.c		\
		src/graphic_process_3.c		\
		src/graphic_process_tools.c	\
		src/graphic_tools.c		\
		src/handle_error.c		\
		src/incantation_manager.c	\
		src/iter.c			\
		src/iter_function.c		\
		src/iter_graphic.c		\
		src/iter_tools.c		\
		src/main.c			\
		src/map.c			\
		src/max_fd.c			\
		src/msgout_cmd_1.c		\
		src/msgout_cmd_2.c		\
		src/msgout_cmd_3.c		\
		src/my_receive.c		\
		src/my_send.c			\
		src/network.c			\
		src/parse_arg.c			\
		src/player.c			\
		src/process_function_1.c	\
		src/process_function_2.c	\
		src/process_function_3.c	\
		src/process_graphic_calls_1.c	\
		src/process_graphic_calls_2.c	\
		src/res_manager.c		\
		src/select_manager_1.c		\
		src/select_manager_2.c		\
		src/select_tools.c		\
		src/server_routine.c		\
		src/set_timeout.c		\
		src/sig_manager.c		\
		src/stdout_map.c		\
		src/stdout_player.c		\
		src/stdout_serv.c		\
		src/string_manager.c		\
		src/usage.c			\
		src/var_manager.c		\
		src/victory.c			\
		src/vision_tab.c		\
		src/welcome_graphic.c		\
		src/welcome_player.c

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

