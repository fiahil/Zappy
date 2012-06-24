/*
** msgout_cmd_1.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:21 2012 ulric lefevre
** Last update Sat Jun 23 20:15:22 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"msgout_cmd.h"

void		msgout_broadcast(t_list *out)
{
  list_push_back_new(out, "ok\n", 4);
}

void		msgout_incantation(t_list *out, int lvl)
{
  char		*str;

  asprintf(&str, "elevation en cours\nniveau actuel: %d\n", lvl);
  list_push_back_new(out, str, strlen(str) + 1);
  free(str);
}

void		msgout_fork(t_list *out)
{
  list_push_back_new(out, "ok\n", 4);
}

void		msgout_connect_nbr(t_list *out, char *str)
{
  list_push_back_new(out, str, strlen(str) + 1);
}

void		msgout_mort(t_list *out)
{
  list_push_back_new(out, "mort\n", 6);
}
