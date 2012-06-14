#include <stdlib.h>
#include "def.h"

static void	get_position(int dim, t_map map, int (*coord)[])
{
  int	pos;

  pos = random() % dim;
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
  while (++count < 7)
    ret += stock[count];
  return (ret);
}

static void	put_res_on_map(t_map map, int (*stock)[], int coord[])
{
  t_resource	offset;

  while (!((*stock)[offset = random() % 7]));
  ++map->map[coord[0]][coord[1]]->inv.resources[offset];
  --(*stock)[offset];
}

void	fill_map(t_map map, int dim, int nb_play)
{
  int		stock[7];
  int		counts[2];
  int		coord[2];
  int		nb_res;
  int		nb_sq;

  fill_res_stock(nb_play, &stock);
  nb_sq = (dim / 4) * 3;
  counts[0] = -1;
  while ((++counts[0] < nb_sq) && (count_res(stock)))
    {
      get_position(dim, map, &coord);
      nb_res = (random() % ((count_res(stock) / (nb_sq - counts[0])) - 1) + 1);
      counts[1] = -1;
      while (++counts[1] < nb_res)
	put_res_on_map(map, &stock, coord);
      map->map[coord[0]][coord[1]]->inv.status = TRUE;
    }
  if (count_res(stock))
    {
      get_position(dim, map, &coord);
      while (count_res(stock))
	put_res_on_map(map, &stock, coord);
      map->map[coord[0]][coord[1]]->inv.status = TRUE;
    }
}
