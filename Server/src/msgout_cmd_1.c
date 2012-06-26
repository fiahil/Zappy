/*
** msgout_cmd_1.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:21 2012 ulric lefevre
** Last update Tue Jun 26 13:49:12 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"stdout.h"
#include	"msgout_cmd.h"

void		msgout_broadcast(t_player this)
{
  list_push_back_new(this->cm.out, "ok\n", 4);
  stdout_player_output("ok\n", this->id);
}

void		msgout_incantation(t_player this, int lvl)
{
  char		*str;

  asprintf(&str, "elevation en cours\nniveau actuel: %d\n", lvl);
  list_push_back_new(this->cm.out, str, strlen(str) + 1);
  stdout_player_output(str, this->id);
  free(str);
}

void		msgout_fork(t_player this)
{
  list_push_back_new(this->cm.out, "ok\n", 4);
  stdout_player_output("ok\n", this->id);
}

void		msgout_connect_nbr(t_player this, char *str)
{
  list_push_back_new(this->cm.out, str, strlen(str) + 1);
  stdout_player_output(str, this->id);
}

void		msgout_mort(t_player this)
{
  list_push_back_new(this->cm.out, "mort\n", 6);
  stdout_player_output("mort\n", this->id);
}
