/*
** map.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:31 2012 ulric lefevre
** Last update Wed Jul 11 18:56:57 2012 ulric lefevre
*/

#include	<time.h>
#include	<errno.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"map.h"
#include	"handle_error.h"

t_map		get_map(t_map param)
{
  static t_map	map = NULL;

  if (!param)
    return (map);
  map = param;
  return (map);
}

static void	alloc_map(t_map this, void *pool)
{
  int		y;
  int		x;

  y = 0;
  while (y < this->size_y)
    {
      x = 0;
      if (!(this->map[y] = malloc(sizeof(*(this->map)) * this->size_x)))
	crash_error("malloc", "out_of_memory");
      while (x < this->size_x)
	{
	  this->map[y][x] = pool;
	  this->map[y][x]->inv.status = FALSE;
	  memset(this->map[y][x]->inv.resources, 0,
	      sizeof(this->map[y][x]->inv.resources));
	  this->map[y][x]->players = new_list(NULL, NULL, NULL);
	  pool += sizeof(t_u_square);
	  ++x;
	}
      ++y;
    }
}

void		init_map(int szx, int szy, int nb_team)
{
  t_map		this;
  void		*pool;

  if (!(this = malloc(sizeof(*this))))
    crash_error("malloc", "out_of_memory");
  this->size_x = szx;
  this->size_y = szy;
  if (!(pool = malloc(szx * szy * sizeof(t_u_square))))
    crash_error("malloc", "out_of_memory");
  if (!(this->map = malloc(sizeof(**(this->map)) * szy)))
    crash_error("malloc", "out_of_memory");
  alloc_map(this, pool);
  fill_map(this, (this->size_x * this->size_y), nb_team);
  get_map(this);
}
