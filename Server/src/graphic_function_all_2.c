/*
** graphic_function_all.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Mon Jun 25 15:09:11 2012 ulric lefevre
** Last update Mon Jul  9 17:09:05 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"c_lists.h"
#include	"graphic.h"

void            enw_general(t_list *mn, int egg, int player, t_pos p)
{
  char          *str;

  str = NULL;
  asprintf(&str, "enw %d %d %d %d\n", egg, player, p->x, p->y);
  mn_push(mn, str);
  free(str);
}

void            pnw_general(t_list *mn, t_player play)
{
  char          *str;

  str = NULL;
  if (play->cm.online)
    {
      asprintf(&str, "pnw %d %d %d %d %d %s\n",
               play->id,
               play->pos.x,
               play->pos.y,
               play->dir + 1,
               play->lvl,
               play->team);
      mn_push(mn, str);
      free(str);
    }
}
