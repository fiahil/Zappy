/*
** stdout_map.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Mon Jun 25 14:08:08 2012 ulric lefevre
** Last update Sat Jul  7 11:17:28 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"map.h"
#include	"var_manager.h"

static void	display(t_map map, int x, int y)
{
  while (++x < map->size_x)
    printf("----------");
  printf("-\n");
  while (++y < map->size_y)
    {
      x = -1;
      printf("|");
      while (++x < map->size_x)
	if (count_res(map->map[y][x]->inv.resources))
	  printf(" \033[1;32m%.3d\033[0m \033[1;34m(%zu)\033[0m |",
		 count_res(map->map[y][x]->inv.resources),
		 map->map[y][x]->players->size);
	else
	  printf(" \033[1;31m%.3d\033[0m \033[1;34m(%zu)\033[0m |",
		 count_res(map->map[y][x]->inv.resources),
		 map->map[y][x]->players->size);
      printf("\n---------");
      while (--x)
	printf("----------");
      printf("--\n");
    }
}

void		stdout_map()
{
  int		x;
  int		y;
  t_data_serv	ds;

  x = -1;
  y = -1;
  ds = get_data_serv(NULL);
  if (ds->verbose)
    display(get_map(NULL), x, y);
}
