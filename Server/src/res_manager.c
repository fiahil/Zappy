/*
** res_manager.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sun Jul  1 19:48:45 2012 ulric lefevre
** Last update Mon Jul  2 14:58:30 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"map.h"
#include	"var_manager.h"

void		put_res()
{
  int		x;
  int		y;
  t_map		map;
  t_data_serv	ds;
  int		nb_play;

  map = get_map(NULL);
  ds = get_data_serv(NULL);
  nb_play = ds->player->size;
  while (nb_play)
    {
      x = random() % map->size_x;
      y = random() % map->size_y;
      ++(map->map[y][x]->inv.resources[FOOD]);
      ++(map->map[y][x]->inv.resources[random() % LAST]);
      --nb_play;
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
