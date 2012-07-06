/*
** stdout_player.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Mon Jun 25 13:19:08 2012 ulric lefevre
** Last update Fri Jul  6 11:50:53 2012 ulric lefevre
*/

#include	<time.h>
#include	<stdio.h>
#include	<stdlib.h>

void            stdout_player_status(const char *str, int id)
{
  printf("\033[1;36m");
  printf("%d\t\tJoueur %d : %s\033[0m\n", (int)time(NULL), id, str);
}

void            stdout_player_input(const char *str, int id)
{
  printf("\033[1;32m");
  printf("%d\t\tJoueur %d : %s\033[0m\n", (int)time(NULL), id, str);
}

void            stdout_player_output(const char *str, int id)
{
  printf("\033[1;31m");
  printf("%d\t\tJoueur %d : %s\033[0m", (int)time(NULL), id, str);
}

void            stdout_player_action(const char *str, int id)
{
  printf("\033[1;35m");
  printf("%d\t\tJoueur %d : %s\033[0m\n", (int)time(NULL), id, str);
}
