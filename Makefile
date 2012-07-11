##
## Makefile for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy
## 
## Made by ulric lefevre
## Login   <lefevr_u@epitech.net>
## 
## Started on  Wed Jul 11 04:07:19 2012 ulric lefevre
## Last update Wed Jul 11 04:10:20 2012 ulric lefevre
##

MAKE=           make --no-print-directory

all:
		@$(MAKE) all -C ./AI
		@$(MAKE) all -C ./Server

clean:
		@$(MAKE) clean -C ./AI
		@$(MAKE) clean -C ./Server

fclean:         clean
		@$(MAKE) fclean -C ./AI
		@$(MAKE) fclean -C ./Server

re:             fclean all