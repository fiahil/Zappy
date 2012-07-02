/*
** graphic_function_2.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:16:30 2012 ulric lefevre
** Last update Mon Jul  2 18:58:52 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>

#include	"graphic.h"
#include	"def.h"

void	pnw(t_list *mn, t_player play)
{
  char	*str;

  str = NULL;
  if (!play->cm.online)
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

void	ppo(t_graphic mn, t_player play)
{
  char	*str;

  str = NULL;
  asprintf(&str, "ppo %d %d %d %d\n",
	   play->id,
	   play->pos.x,
	   play->pos.y,
	   play->dir + 1);
  mn_rep(mn, str);
  free(str);
}

void	plv(t_graphic mn, int id, int lvl)
{
  char	*str;

  str = NULL;
  asprintf(&str, "plv %d %d\n", id, lvl);
  mn_rep(mn, str);
  free(str);
}

void	pin(t_graphic mn, t_player play)
{
  char	*str;

  str = NULL;
  asprintf(&str, "pin %d %d %d %d %d %d %d %d %d %d\n",
	   play->id,
	   play->pos.x,
	   play->pos.y,
	   play->inv.resources[FOOD],
	   play->inv.resources[LINEMATE],
	   play->inv.resources[DERAUMERE],
	   play->inv.resources[SIBUR],
	   play->inv.resources[MENDIANE],
	   play->inv.resources[PHIRAS],
	   play->inv.resources[THYSTAME]);
  mn_rep(mn, str);
  free(str);
}

void	pex(t_list *mn, int id)
{
  char	*str;

  str = NULL;
  asprintf(&str, "pex %d\n", id);
  mn_push(mn, str);
  free(str);
}
