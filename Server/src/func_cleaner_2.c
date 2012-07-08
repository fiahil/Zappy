/*
** func_cleaner_2.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Tue Jun 26 11:14:45 2012 ulric lefevre
** Last update Sun Jul  8 11:42:20 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"map.h"

int		action_cleaner(void *ptr, size_t s)
{
  (void)s;
  if (((t_player_action)ptr)->done == TRUE)
    {
      free(((t_player_action)ptr)->param);
      return (1);
    }
  return (0);
}

int		egg_cleaner(void *ptr, size_t s)
{
  (void)s;
  if (!((t_egg)ptr)->status)
    return (1);
  return (0);
}

void		clean_all(t_data_serv ds)
{
  t_map		map;
  int		x;
  int		y;

  delete_list(ds->monitor);
  delete_list(ds->player);
  delete_list(ds->teams);
  delete_pqueue(ds->action);
  delete_list(ds->send_q);
  delete_list(ds->egg);
  map = get_map(NULL);
  y = 0;
  while (y < map->size_y)
    {
      x = 0;
      while (x < map->size_x)
	delete_list(map->map[y][x++]->players);
      ++y;
    }
  free(map->map[0][0]);
  x = 0;
  while (x < map->size_y)
    free(map->map[x++]);
  free(map->map);
  free(map);
}
