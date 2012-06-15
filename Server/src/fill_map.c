#include <stdio.h>
#include <stdlib.h>
#include "def.h"

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

static void	fill_res_stock(int nb_play, int (*stock)[])
{
  (*stock)[FOOD] = nb_play * 100;
  (*stock)[LINEMATE] = (nb_play * 9) * 2;
  (*stock)[DERAUMERE] = (nb_play * 8) * 2;
  (*stock)[SIBUR] = (nb_play * 10) * 2;
  (*stock)[MENDIANE] = (nb_play * 5) * 2;
  (*stock)[PHIRAS] = (nb_play * 6) * 2;
  (*stock)[THYSTAME] = nb_play * 2;
}

static int	count_res(int stock[])
{
  int	count;
  int	ret;

  ret = 0;
  count = -1;
  while (++count < LAST)
    ret += stock[count];
  return (ret);
}

static void	put_res_on_map(t_map map, int (*stock)[], int coord[])
{
  t_resource	offset;

  while (!((*stock)[offset = random() % LAST]));
  ++map->map[coord[0]][coord[1]]->inv.resources[offset];
  --(*stock)[offset];
}

void	display(t_map map)
{
  int	x;
  int	y;

  y = -1;
  x = -1;
  while (++x < map->size_x)
    printf("------");
  printf("-");
  printf("\n");
  while (++y < map->size_y)
    {
      x = -1;
      printf("|");
      while (++x < map->size_x)
	if (count_res(map->map[y][x]->inv.resources))
	  printf(" \033[1;32m%.3d\033[0m |", count_res(map->map[y][x]->inv.resources));
	else
	  printf(" \033[1;31m%.3d\033[0m |", count_res(map->map[y][x]->inv.resources));
      printf("\n");
      printf("-----");
      while (--x)
	printf("------");
      printf("--");
      printf("\n");
    }
}

void	fill_map(t_map map, int dim, int nb_play)
{
  int		stock[LAST];
  int		counts[2];
  int		coord[2];
  int		nb_res;

  fill_res_stock(nb_play, &stock);
  counts[0] = -1;
  fprintf(stdout, ".::: map_fill.c :::.\n\n(To remove this display, see in fill_map.c at lines 99, 100 and 111)");
  fprintf(stdout, "Nb play = %d\nTotal res = %d\n\tFOOD = %d\n\tLINEMATE = %d\n\tDERAUMERE = %d\n\tSIBUR = %d\n\tMENDIANE = %d\n\tPHIRAS = %d\n\tTHYSTAME = %d\n\n", nb_play, count_res(stock), stock[0], stock[1], stock[2], stock[3], stock[4], stock[5], stock[6]);
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
  display(map);
}
