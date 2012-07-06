/*
** process_function_3.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:14:19 2012 ulric lefevre
** Last update Fri Jul  6 16:24:23 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"map.h"
#include	"graphic.h"
#include	"algorithm.h"
#include	"msgout_cmd.h"
#include	"process_function.h"

static const int	g_dir[4][2] =
  {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0}
  };

static const int	g_src[4][4] =
  {
    {5, 7, 1, 3},
    {3, 5, 7, 1},
    {1, 3, 5, 7},
    {7, 1, 3, 5}
  };

int		cmp_player_list(void *ptr1, size_t sz1, void *ptr2, size_t sz2)
{
  (void)sz1;
  (void)sz2;
  if ((*((t_player*)ptr1)) == ((t_player)(ptr2)))
    return (0);
  else
    return (1);
}

static void	do_move_process(t_player this, int coef_x, int coef_y)
{
  t_map		map;
  t_u_pos	prec;
  t_iter	*tmp;

  tmp = NULL;
  prec.x = this->pos.x;
  prec.y = this->pos.y;
  map = get_map(NULL);
  this->pos.x += coef_x;
  this->pos.y += coef_y;
  if (this->pos.x >= map->size_x)
    this->pos.x = 0;
  if (this->pos.x < 0)
    this->pos.x = map->size_x - 1;
  if (this->pos.y >= map->size_y)
    this->pos.y = 0;
  if (this->pos.y < 0)
    this->pos.y = map->size_y - 1;
  tmp = list_find_cmp(map->map[prec.y][prec.x]->players,
		      &cmp_player_list, this, sizeof(*this));
  list_extract(map->map[prec.y][prec.x]->players, tmp);
  list_push_back(map->map[this->pos.y][this->pos.x]->players, tmp);
}

t_bool		move_process(t_player this, char *data, t_data_serv info)
{
  (void)data;
  (void)info;
  do_move_process(this, g_dir[this->dir][0], g_dir[this->dir][1]);
  msgout_avance(this);
  ppo_general(info->monitor, this);
  return (TRUE);
}

t_bool		expulse_process(t_player this, char *data, t_data_serv info)
{
  t_list	*players;
  t_iter	*ti;
  t_player	*p;
  t_map		map;

  (void)data;
  (void)info;
  map = get_map(NULL);
  players = map->map[this->pos.y][this->pos.x]->players;
  ti = list_find_cmp(players, &cmp_player_list, this, sizeof(*this));
  list_extract(players, ti);
  msgout_expulse(this, players->size ? TRUE : FALSE);
  expulse_graphic(info->monitor, this,
		  map->map[this->pos.y][this->pos.x]->players);
  while (players->size)
    {
      p = list_front(players);
      do_move_process(*p, g_dir[this->dir][0],
		      g_dir[this->dir][1]);
    }
  list_push_back(players, ti);
  return (TRUE);
}

t_bool		inventory_process(t_player this, char *data, t_data_serv info)
{
  (void)data;
  (void)info;
  msgout_inventaire(this, this->inv);
  return (TRUE);
}
