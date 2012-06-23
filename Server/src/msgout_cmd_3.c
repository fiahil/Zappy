/*
** msgout_cmd_3.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:13 2012 ulric lefevre
** Last update Sat Jun 23 20:15:14 2012 ulric lefevre
*/

#include	"msgout_cmd.h"

void		msgout_avance(t_list *out)
{
  list_push_back_new(out, "ok\n", 4);
}

void		msgout_droite(t_list *out)
{
  list_push_back_new(out, "ok\n", 4);
}

void		msgout_gauche(t_list *out)
{
  list_push_back_new(out, "ok\n", 4);
}

void		msgout_fail(t_list *out)
{
  list_push_back_new(out, "ko\n", 4);
}
