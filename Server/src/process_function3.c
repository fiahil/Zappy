/*
 * Fiahil
 * 06.06.2012
 */

#include <stdlib.h>
#include <string.h>
#include "process_function.h"
#include "map.h"
#include "my_itoa.h"

static void	do_move_process(t_player this, int coef_x, int coef_y)
{
  t_map	map;

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
  // TODO : deplacement du joueur ok,
  //   mais pas de deplacement dans la map
  //   (dans la listes des joueurs sur la map)
}

t_bool  move_process_function(t_player this, char *data)
{
  (void)data;
  if (this->dir == NORTH)
    do_move_process(this, 0, -1);
  else if (this->dir == EAST)
    do_move_process(this, 1, 0);
  else if (this->dir == SOUTH)
    do_move_process(this, 0, 1);
  else
    do_move_process(this, -1, 0);
  // TODO tmp

  char *str = malloc(sizeof(*str) * (strlen("I move in        :        !\n") + 1));
  memset(str, 0, strlen("I move in        :        !\n"));
  strcat(strcat(strcat(strcat(strcat(str, "I move in "), my_itoa(this->pos.x)), " : "), my_itoa(this->pos.y)), " !\n");

  // TODO tmp/
  list_push_back_new(this->cm.out, str, strlen(str) + 1);
  free(str); // TODO

  return (TRUE);
}

t_bool  right_process_function(t_player this, char *data)
{
  (void)data;
  if (this->dir == WEST)
    this->dir = NORTH;
  else
    this->dir += 1;
  list_push_back_new(this->cm.out, "I turn right !\n", strlen("I turn right !\n") + 1);
  return (TRUE);
}

t_bool  left_process_function(t_player this, char *data)
{
  (void)data;
  if (this->dir == NORTH)
    this->dir = WEST;
  else
    this->dir -= 1;
  list_push_back_new(this->cm.out, "I turn left !\n", strlen("I turn left !\n") + 1);
  return (TRUE);
}
