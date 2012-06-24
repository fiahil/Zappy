#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "c_lists.h"
#include "graphic.h"
#include "def.h"

void	ppo_general(t_list *mn, t_player play)
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

void	pin_general(t_list *mn, t_player play)
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

void	bct_general(t_list *mn, t_square sq, t_pos p)
{
  char		*str;

  str = NULL;
  asprintf(&str, "bct %d %d %d %d %d %d %d %d %d\n", p->x, p->y,
      sq->inv.resources[FOOD],
      sq->inv.resources[LINEMATE],
      sq->inv.resources[DERAUMERE],
      sq->inv.resources[SIBUR],
      sq->inv.resources[MENDIANE],
      sq->inv.resources[PHIRAS],
      sq->inv.resources[THYSTAME]);
  mn_push(mn, str);
  free(str);
}
