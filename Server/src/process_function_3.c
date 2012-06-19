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

t_bool  move_process_function(t_player this, char *data)
{
  char *str;

  (void)data;
  if (this->dir == NORTH)
    do_move_process(this, 0, -1);
  else if (this->dir == EAST)
    do_move_process(this, 1, 0);
  else if (this->dir == SOUTH)
    do_move_process(this, 0, 1);
  else
    do_move_process(this, -1, 0);
  str = NULL;
  asprintf(&str, "I move in %d : %d !\n", this->pos.x, this->pos.y); // TODO:TMP
  list_push_back_new(this->cm.out, str, strlen(str) + 1);
  free(str); // TODO:TMP

  msgout_avance(this->cm.out);
  return (TRUE);
}

t_bool  right_process_function(t_player this, char *data)
{
  (void)data;
  if (this->dir == WEST)
    this->dir = NORTH;
  else
    this->dir += 1;
  list_push_back_new(this->cm.out, "I turn right !\n",
		     strlen("I turn right !\n") + 1);
  msgout_droite(this->cm.out);
  return (TRUE);
}

t_bool  left_process_function(t_player this, char *data)
{
  (void)data;
  if (this->dir == NORTH)
    this->dir = WEST;
  else
    this->dir -= 1;
  list_push_back_new(this->cm.out, "I turn left !\n",
		     strlen("I turn left !\n") + 1);
  msgout_gauche(this->cm.out);
  return (TRUE);
}

