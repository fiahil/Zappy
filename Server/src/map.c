/*
** map.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:31 2012 ulric lefevre
** Last update Sun Jun 24 15:40:44 2012 ulric lefevre
*/

#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "handle_error.h"

t_map		get_map(t_map param)
{
  static t_map	map = NULL;

  if (!param)
    return (map);
  map = param;
  return (map);
}

static void	malloc_error()
{
  // TODO error
  handle_error("malloc", strerror(errno), -1);
  exit(1);
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
	malloc_error();
      while (x < this->size_x)
	{
	  this->map[y][x] = pool;
	  this->map[y][x]->inv.status = FALSE;
	  memset(this->map[y][x]->inv.resources,
		 0,
		 sizeof(this->map[y][x]->inv.resources));
	  this->map[y][x]->players = new_list(NULL, NULL, NULL);
	  pool += sizeof(t_u_square);
	  ++x;
	}
      ++y;
    }
}

void		init_map(int szx, int szy, int nb_play)
{
  t_map		this;
  void		*pool;

  if (!(this = malloc(sizeof(*this))))
    malloc_error();
  this->size_x = szx;
  this->size_y = szy;
  if (!(pool = malloc(szx * szy * sizeof(t_u_square))))
    malloc_error();
  if (!(this->map = malloc(sizeof(**(this->map)) * szy)))
    malloc_error();
  alloc_map(this, pool);
  fill_map(this, (this->size_x * this->size_y), nb_play);
  get_map(this);
}
