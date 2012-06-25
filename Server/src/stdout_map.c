/*
** stdout_map.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Mon Jun 25 14:08:08 2012 ulric lefevre
** Last update Mon Jun 25 14:42:02 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"map.h"

static void	display(t_map map)
{
  int	x;
  int	y;

  y = -1;
  x = -1;
  while (++x < map->size_x)
    printf("----------");
  printf("-");
  printf("\n");
  while (++y < map->size_y)
    {
      x = -1;
      printf("|");
      while (++x < map->size_x)
	if (count_res(map->map[y][x]->inv.resources))
	  printf(" \033[1;32m%.3d\033[0m \033[1;34m(%zu)\033[0m |", count_res(map->map[y][x]->inv.resources), map->map[y][x]->players->size);
	else
	  printf(" \033[1;31m%.3d\033[0m \033[1;34m(%zu)\033[0m |", count_res(map->map[y][x]->inv.resources), map->map[y][x]->players->size);
      printf("\n");
      printf("---------");
      while (--x)
	printf("----------");
      printf("--");
      printf("\n");
    }
}

void		stdout_map()
{
  t_map		map;

  map = get_map(NULL);
  display(map);
}
