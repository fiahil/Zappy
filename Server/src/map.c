/*
** map.c for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/src/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on Tue Jun 12 11:00:09 2012 benjamin businaro
8** Last update Tue Jun 12 11:50:59 2012 benjamin businaro
*/

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "handle_error.h"
#include "map.h"

t_map	get_map(t_map param)
{
  static t_map map = NULL;

  if (!param)
    return (map);
  map = param;
  return (map);
}

static void	malloc_error()
{
  // TODO error
  handleError("malloc", strerror(errno), -1);
  exit(1);
}

void	init_map(int szx, int szy, int nb_play)
{
  t_map this;
  void	*pool;
  int	y;
  int	x;

  y = 0;
  if (!(this = malloc(sizeof(*this))))
    malloc_error();
  this->size_x = szx;
  this->size_y = szy;
  if (!(pool = malloc(szx * szy * sizeof(t_u_square))))
    malloc_error();
  if (!(this->map = malloc(sizeof(**(this->map)) * szy)))
    malloc_error();
  while (y < szy)
    {
      x = 0;
      if (!(this->map[y] = malloc(sizeof(*(this->map)) * szx)))
	malloc_error();
      while (x < szx)
	{
	  this->map[y][x] = pool;
	  this->map[y][x]->inv.status = FALSE;
	  memset(this->map[y][x]->inv.resources, 0, sizeof(this->map[y][x]->inv.resources));
	  init_list(&(this->map[y][x]->client), NULL, NULL, NULL);
	  pool += sizeof(t_u_square);
	  ++x;
	}
      ++y;
    }
  fill_map(this, (this->size_x * this->size_y), nb_play);
  get_map(this);
}
