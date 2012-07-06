/*
** msgout_cmd_3.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:13 2012 ulric lefevre
** Last update Fri Jul  6 11:55:38 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"stdout.h"
#include	"msgout_cmd.h"

void		msgout_avance(t_player this)
{
  list_push_back_new(this->cm.out, "ok\n", 4);
  stdout_player_output("ok\n", this->id);
}

void		msgout_droite(t_player this)
{
  list_push_back_new(this->cm.out, "ok\n", 4);
  stdout_player_output("ok\n", this->id);
}

void		msgout_gauche(t_player this)
{
  list_push_back_new(this->cm.out, "ok\n", 4);
  stdout_player_output("ok\n", this->id);
}

void		msgout_fail(t_player this)
{
  list_push_back_new(this->cm.out, "ko\n", 4);
  stdout_player_output("ko\n", this->id);
}

void		msgout_moved(t_player this, int dir)
{
  char		*str;

  str = NULL;
  asprintf(&str, "deplacement %d\n", dir);
  list_push_back_new(this->cm.out, str, strlen(str) + 1);
  free(str);
  stdout_player_output("a bougé\n", this->id);
}
