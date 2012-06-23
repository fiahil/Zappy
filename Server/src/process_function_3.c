/*
 * Fiahil
 * 06.06.2012
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "my_itoa.h"
#include "msgout_cmd.h"
#include "process_function.h"
#include "algorithm.h"

static const int	g_dir[4][2] = {
  { 0, -1},
  { 1, 0},
  { 0, 1},
  { -1, 0}
};

static const int	g_src[4][4] = {
  { 5, 7, 1, 3},
  { 3, 5, 7, 1},
  { 1, 3, 5, 7},
  { 7, 1, 3, 5}
};

static int	cmp_player_list(void *ptr1, size_t sz1, void *ptr2, size_t sz2)
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
  tmp = list_find_cmp(get_map(NULL)->map[prec.y][prec.x]->players,
		      &cmp_player_list, this, sizeof(*this));
  list_extract(get_map(NULL)->map[prec.y][prec.x]->players, tmp);
  list_push_back(get_map(NULL)->map[this->pos.y][this->pos.x]->players, tmp);
}

t_bool  move_process_function(t_player this, char *data, t_data_serv info)
{
  char *str;

  (void)data;
  (void)info;
  /* if (this->dir == NORTH) */
  /*   do_move_process(this, 0, -1); */
  /* else if (this->dir == EAST) */
  /*   do_move_process(this, 1, 0); */
  /* else if (this->dir == SOUTH) */
  /*   do_move_process(this, 0, 1); */
  /* else */
  /*   do_move_process(this, -1, 0); */
  do_move_process(this, g_dir[this->dir][0], g_dir[this->dir][1]);
  str = NULL;
  asprintf(&str, "I move in %d : %d !\n", this->pos.x, this->pos.y); // TODO:TMP
  list_push_back_new(this->cm.out, str, strlen(str) + 1);
  free(str); // TODO:TMP

  msgout_avance(this->cm.out);
  return (TRUE);
}

t_bool		expulse_process_function(t_player this, char *data, t_data_serv info)
{
  char		*msg;
  t_list	*players;
  t_iter	*ti;
  t_player	*p;

  (void)data;
  (void)info;
  players = get_map(NULL)->map[this->pos.y][this->pos.x]->players;
  ti = list_find_cmp(players, &cmp_player_list, this, sizeof(*this));
  list_extract(players, ti);
  msgout_expulse(this->cm.out, players->size ? TRUE : FALSE);
  while (players->size)
    {
      p = list_front(players);
      do_move_process(*p, g_dir[this->dir][0],
		      g_dir[this->dir][1]);
      msg = NULL;
      asprintf(&msg, "deplacement: %d\n",
	       g_src[this->dir][(*p)->dir]);
      list_push_back_new((*p)->cm.out, msg, strlen(msg) + 1);
      free(msg);
    }
  list_push_back(players, ti);
  return (TRUE);
}

t_bool		inventory_process_function(t_player this, char *data, t_data_serv info)
{
  (void)data;
  (void)info;
  msgout_inventaire(this->cm.out, this->inv);
  return (TRUE);
}
