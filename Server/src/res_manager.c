/*
** res_manager.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sun Jul  1 19:48:45 2012 ulric lefevre
** Last update Tue Jul  3 13:52:47 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"map.h"
#include	"graphic.h"
#include	"var_manager.h"

void		put_res(int val)
{
  static int	last_val = 0;
  int		i;
  t_u_pos	pos;
  t_map		map;
  t_data_serv	ds;

  last_val += val;
  i = last_val / 300;
  last_val %= 300;
  map = get_map(NULL);
  ds = get_data_serv(NULL);
  while (i)
    {
      pos.x = random() % map->size_x;
      pos.y = random() % map->size_y;
      map->map[pos.y][pos.x]->inv.resources[FOOD] += random() % 4 + 1;
      map->map[pos.y][pos.x]->inv.resources[random() % (LAST - 1) + 1]
	+= random() % 2 + 1;
      bct_general(ds->monitor, map->map[pos.y][pos.x], &pos);
      --i;
    }
}

void		put_inv(t_inventory inv)
{
  t_u_pos	pos;
  t_resource	res;
  t_map		map;
  t_data_serv	ds;

  res = FOOD;
  map = get_map(NULL);
  ds = get_data_serv(NULL);
  while (res != LAST)
    {
      while (inv->resources[res])
	{
	  pos.x = random() % map->size_x;
	  pos.y = random() % map->size_y;
	  --(inv->resources[res]);
	  ++(map->map[pos.y][pos.x]->inv.resources[res]);
	  bct_general(ds->monitor, map->map[pos.y][pos.x], &pos);
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
  t_u_pos	pos;
  t_map		map;
  t_resource	res;
  int		new[LAST];
  t_data_serv	ds;

  init_res_tab(&new);
  map = get_map(NULL);
  ds = get_data_serv(NULL);
  res = FOOD;
  while (res != LAST)
    {
      while (new[res])
	{
	  pos.x = random() % map->size_x;
	  pos.y = random() % map->size_y;
	  --(new[res]);
	  ++(map->map[pos.y][pos.x]->inv.resources[res]);
	  bct_general(ds->monitor, map->map[pos.y][pos.x], &pos);
	}
      ++res;
    }
}
