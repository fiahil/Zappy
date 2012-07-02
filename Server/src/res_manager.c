/*
** res_manager.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sun Jul  1 19:48:45 2012 ulric lefevre
** Last update Mon Jul  2 23:02:54 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"map.h"
#include	"var_manager.h"

void		put_res(int val)
{
  static int	last_val = 0;
  int		i;
  int		x;
  int		y;
  t_map		map;

  last_val += val;
  i = last_val / 300;
  last_val %= 300;
  map = get_map(NULL);
  while (i)
    {
      x = random() % map->size_x;
      y = random() % map->size_y;
      map->map[y][x]->inv.resources[FOOD] += random() % 4 + 1;
      map->map[y][x]->inv.resources[random() % (LAST - 1) + 1]
	+= random() % 2 + 1;
      --i;
    }
}

void		put_inv(t_inventory inv)
{
  int		x;
  int		y;
  t_resource	res;
  t_map		map;

  res = FOOD;
  map = get_map(NULL);
  while (res != LAST)
    {
      while (inv->resources[res])
	{
	  x = random() % map->size_x;
	  y = random() % map->size_y;
	  --(inv->resources[res]);
	  ++(map->map[y][x]->inv.resources[res]);
	}
      ++res;
    }
}

static void	init_res_tab(int (*new)[])
{
  (*new)[FOOD] = 100;
  (*new)[LINEMATE] = 18;
  (*new)[DERAUMERE] = 16;
  (*new)[SIBUR] = 20;
  (*new)[MENDIANE] = 10;
  (*new)[PHIRAS] = 12;
  (*new)[THYSTAME] = 2;
}

void		put_res_egg()
{
  int		x;
  int		y;
  t_map		map;
  t_resource	res;
  int		new[LAST];

  init_res_tab(&new);
  map = get_map(NULL);
  res = FOOD;
  while (res != LAST)
    {
      while (new[res])
	{
	  x = random() % map->size_x;
	  y = random() % map->size_y;
	  --(new[res]);
	  ++(map->map[y][x]->inv.resources[res]);
	}
      ++res;
    }
}
