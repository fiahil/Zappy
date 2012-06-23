/*
 * Texan
 *23/06/2012
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "graphic.h"
#include "def.h"

void	pnw(t_list *mn, t_player play)
{
  char	*str;

  str = NULL;
  asprintf(&str, "pnw #%d %d %d %d %d %s\n",
	   play->id,
	   play->pos.x,
	   play->pos.y,
	   play->dir + 1,
	   play->lvl,
	   play->team);
  mn_push(mn, str);
  free(str);
}

void	ppo(t_list *mn, t_player play)
{
  char	*str;

  str = NULL;
  asprintf(&str, "ppo #%d %d %d %d\n",
	   play->id,
	   play->pos.x,
	   play->pos.y,
	   play->dir + 1);
  mn_push(mn, str);
  free(str);
}

void	plv(t_list *mn, int id, int lvl)
{
  char	*str;

  str = NULL;
  asprintf(&str, "plv #%d %d\n", id, lvl);
  mn_push(mn, str);
  free(str);
}

void	pin(t_list *mn, t_player play)
{
  char	*str;

  str = NULL;
  asprintf(&str, "pin #%d %d %d %d %d %d %d %d %d %d\n",
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
  mn_push(mn, str);
  free(str);
}

void	pex(t_list *mn, int id)
{
  char	*str;

  str = NULL;
  asprintf(&str, "pex #%d\n", id);
  mn_push(mn, str);
  free(str);
}
