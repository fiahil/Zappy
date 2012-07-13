/*
** res_manager.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sun Jul  1 19:48:45 2012 ulric lefevre
** Last update Sat Jul 14 00:44:02 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"map.h"
#include	"graphic.h"
#include	"var_manager.h"

void		put_food(int val)
{
  t_data_serv	ds;
  static int	last_val = 0;
  int		i;
  t_u_pos	pos;
  t_map		map;
  int		div;

  ds = get_data_serv(NULL);
  i = 0;
  if (ds->player->size)
    {
      last_val = last_val + val;
      div = (ds->player->size > 100) ? (100) : (ds->player->size);
      i = last_val / (100 / div);
      last_val %= (100 / div);
    }
  map = get_map(NULL);
  while (i)
    {
      pos.x = random() % map->size_x;
      pos.y = random() % map->size_y;
      map->map[pos.y][pos.x]->inv.resources[FOOD] += 1;
      bct_general(ds->monitor, map->map[pos.y][pos.x], &pos);
      --i;
    }
}

void		put_rock(int val)
{
  t_data_serv	ds;
  static int	last_val = 0;
  int		i;
  t_u_pos	pos;
  t_map		map;
  int		div;

  ds = get_data_serv(NULL);
  i = 0;
  if (ds->player->size)
    {
      last_val += val;
      div = (ds->player->size > 100) ? (100) : (ds->player->size);
      i = last_val / (1000 / div);
      last_val %= (1000 / div);
    }
  map = get_map(NULL);
  while (i)
    {
      pos.x = random() % map->size_x;
      pos.y = random() % map->size_y;
      map->map[pos.y][pos.x]->inv.resources[random() % (LAST - 1) + 1] += 1;
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
      while (inv->resources[res] > 0)
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
  (*new)[FOOD] = 40;
  (*new)[LINEMATE] = 0;
  (*new)[DERAUMERE] = 0;
  (*new)[SIBUR] = 0;
  (*new)[MENDIANE] = 0;
  (*new)[PHIRAS] = 0;
  (*new)[THYSTAME] = 0;
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
