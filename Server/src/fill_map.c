/*
** fill_map.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:17:00 2012 ulric lefevre
** Last update Fri Jul 13 17:12:59 2012 ulric lefevre
*/

#include	<math.h>
#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"stdout.h"

static void	get_position(int dim, t_map map, int (*coord)[])
{
  t_bool	is_full;
  int		pos;
  int		x;
  int		y;

  y = -1;
  is_full = TRUE;
  while ((++y < map->size_y) && is_full)
    {
      x = -1;
      while ((++x < map->size_x) && is_full)
	if (!map->map[y][x]->inv.status)
	  is_full = FALSE;
    }
  pos = random() % dim;
  if (!is_full)
    while (map->map[pos / map->size_x][pos % map->size_x]->inv.status)
      pos = random() % dim;
  (*coord)[0] = pos / map->size_x;
  (*coord)[1] = pos % map->size_x;
}

static void	fill_res_stock(t_map map, int nb_team, int (*stock)[])
{
  int		n;

  n = ceil((float)map->size_x / 10.0) * ceil((float)map->size_y / 10.0);
  (*stock)[FOOD] = nb_team * 100 * n;
  (*stock)[LINEMATE] = nb_team * 9 * n;
  (*stock)[DERAUMERE] = nb_team * 8 * n;
  (*stock)[SIBUR] = nb_team * 10 * n;
  (*stock)[MENDIANE] = nb_team * 5 * n;
  (*stock)[PHIRAS] = nb_team * 6 * n;
  (*stock)[THYSTAME] = nb_team * 1 * n;
}

static void	put_res_on_map(t_map map, int (*stock)[], int coord[])
{
  t_resource	offset;

  while (!((*stock)[offset = random() % LAST]));
  ++map->map[coord[0]][coord[1]]->inv.resources[offset];
  --(*stock)[offset];
}

int		count_res(int stock[])
{
  int		count;
  int		ret;

  ret = 0;
  count = -1;
  while (++count < LAST)
    ret += stock[count];
  return (ret);
}

void		fill_map(t_map map, int dim, int nb_team)
{
  int		stock[LAST];
  int		counts[2];
  int		coord[2];
  int		nb_res;

  fill_res_stock(map, nb_team, &stock);
  counts[0] = -1;
  while (count_res(stock))
    {
      get_position(dim, map, &coord);
      if ((nb_res = random() % (10 - 1) + 1) > count_res(stock))
	nb_res = count_res(stock);
      counts[1] = -1;
      while (++counts[1] < nb_res)
	put_res_on_map(map, &stock, coord);
      map->map[coord[0]][coord[1]]->inv.status = TRUE;
    }
}
