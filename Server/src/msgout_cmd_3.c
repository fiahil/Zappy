/*
** msgout_cmd_3.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:13 2012 ulric lefevre
** Last update Mon Jun 25 17:49:10 2012 ulric lefevre
*/

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
