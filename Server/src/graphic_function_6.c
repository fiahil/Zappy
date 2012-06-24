/*
 * Fiahil
 * 23/06/2012
 */
  
#define _GNU_SOURCE
  
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graphic.h"
#include "def.h"

void		bct(t_graphic mn, t_square sq, t_pos p)
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
  mn_rep(mn, str);
  free(str);
}

void		bct_all(t_graphic mn, t_map map)
{
  int		x;
  int		y;
  t_u_pos	p;

  y = 0;
  while (y < map->size_y)
  {
    x = 0;
    while (x < map->size_x)
    {
      p.x = x;
      p.y = y;
      bct(mn, map->map[y][x], &p);
      x++;
    }
    y++;
  }
}
