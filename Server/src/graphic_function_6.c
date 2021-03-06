/*
** graphic_function_6.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Mon Jun 25 15:09:31 2012 ulric lefevre
** Last update Fri Jul  6 13:08:22 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>

#include	"def.h"
#include	"graphic.h"

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

void		sgt(t_graphic mn, int t)
{
  char		*str;

  str = NULL;
  asprintf(&str, "sgt %d\n", t);
  mn_rep(mn, str);
  free(str);
}
