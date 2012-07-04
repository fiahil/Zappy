/*
** broadcast.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:17:20 2012 ulric lefevre
** Last update Wed Jul  4 13:53:26 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<math.h>
#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>

#include	"def.h"
#include	"map.h"
#include	"c_lists.h"

static const int	g_quarter[4][3] =
  {
    { 6, 5, 4 },
    { 2, 3, 4 },
    { 6, 7, 0 },
    { 2, 1, 0 }
  };

static const t_u_pos	g_out_pos[8] =
  {
    { 1, 0 },
    { 0, 1 },
    { 1, 1 },
    { -1, 0 },
    { 0, -1 },
    { -1, 1 },
    { 1, -1 },
    { -1, -1 }
  };

static void	get_closest_pos(t_u_pos *src, t_u_pos *dest, t_u_pos *close)
{
  int		i;
  t_u_pos	coord;
  t_map		map;
  double	tmp1;
  double	tmp2;

  i = 0;
  map = get_map(NULL);
  close->x = src->x;
  close->y = src->y;
  while (i < 8)
    {
      coord.x = src->x + g_out_pos[i].x * map->size_x;
      coord.y = src->y + g_out_pos[i].y * map->size_y;
      tmp1 = sqrt(pow(close->x - dest->x, 2.0) + pow(close->y - dest->y, 2.0));
      tmp2 = sqrt(pow(coord.x - dest->x, 2.0) + pow(coord.y - dest->y, 2.0));
      if (tmp2 < tmp1)
	{
	  close->x = coord.x;
	  close->y = coord.y;
	}
      ++i;
    }
}

static int	where_does_it_come_from(t_u_pos *dest, t_u_pos *src)
{
  int		x;
  int		y;
  int		i;
  int		ret;
  double	p;

  x = src->x - dest->x;
  y = src->y - dest->y;
  i = (x > 0 ? 0 : 1) + 2 * (y > 0 ? 0 : 1);
  if (!x && !y)
    return (-1);
  if (x != 0)
    {
      p = (double)ABS(y) / (double)ABS(x);
      if (p < 0.5)
	ret = g_quarter[i][0];
      else if (p >= 0.5 && p <= 2.0)
	ret = g_quarter[i][1];
      else
	ret = g_quarter[i][2];
    }
  else
    ret = y > 0 ? 4 : 0;
  return (ret);
}

void		message(t_player src, t_player dest, char *txt)
{
  int		dir;
  char		*msg;
  t_u_pos	tmp;

  if (src != dest)
    {
      get_closest_pos((&src->pos), &(dest->pos), &tmp);
      dir = where_does_it_come_from(&(dest->pos), &tmp);
      if (dir >= 0)
	dir = ((dir + (dest->dir * 2)) % 8);
      ++dir;
      asprintf(&msg, "message %d,%s\n", dir, txt);
      list_push_back_new(dest->cm.out, msg, strlen(msg) + 1);
      free(msg);
    }
}
