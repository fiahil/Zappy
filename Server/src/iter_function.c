/*
** iter_function.c for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/Server/src/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on Sat Jun 16 16:11:56 2012 benjamin businaro
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "handle_error.h"
#include "iter_function.h"
#include "map.h"
#include "clock.h"

int	action_cleaner(void *ptr, size_t s)
{
  (void)s;
  if ((*(t_player_action*)ptr)->done == TRUE)
    {
      free((*(t_player_action*)ptr)->param);
      return (1);
    }
  return (0);
}

t_player	init_player()
{
  t_player player;

  if (!(player = malloc(sizeof(t_u_player))))
    handleError("malloc", strerror(errno), -1); // TODO retour erreur
  player->lvl = 1;
  player->team = NULL;
  player->pos.x = random() % get_map(NULL)->size_x;
  player->pos.y = random() % get_map(NULL)->size_y;
  player->dir = random() % 4;
  player->dead = FALSE;
  player->welcome = FALSE;
  player->inv.status = FALSE;
  memset(player->inv.resources, '\0', sizeof(int) * LAST);
  player->inv.resources[FOOD] = 10;
  player->inv.cur_life = 127;
  memset(player->cm.stock, '\0', sizeof(player->cm.stock));
  player->cm.in = new_list(NULL, NULL, NULL);
  player->cm.out = new_list(NULL, NULL, NULL);
  player->cm.mode = UNKNOW;
  player->cm.is_processing = FALSE;
  player->cm.online = FALSE;
  list_push_back_new(get_map(NULL)->map[player->pos.y][player->pos.x]->players,
		     &player, sizeof(&player));
  return (player);
}

int	sort_player_life(void *ptr1, size_t sz1, void *ptr2, size_t sz2)
{
  int	val1;
  int	val2;

  (void)sz1;
  (void)sz2;
  val1 = 0;
  val2 = 0;
  if ((*((t_player*)(ptr1)))->inv.resources[FOOD] <= 0)
    val1 = ((*((t_player*)(ptr1)))->inv.resources[FOOD] - 1)
      * 127 + (*((t_player*)(ptr1)))->inv.cur_life;
  if ((*((t_player*)(ptr2)))->inv.resources[FOOD] <= 0)
    val2 = ((*((t_player*)(ptr2)))->inv.resources[FOOD] - 1)
      * 127 + (*((t_player*)(ptr2)))->inv.cur_life;
  if (val1 > val2)
    return (1);
  if (val1 < val2)
    return (-1);
  return (0);
}



static void	set_timeout_action(t_player_action *ptr, t_timeval time)
{
  t_u_timeval	current;

  if (!ptr)
    {
      time->tv_usec = 1000;
      time->tv_sec = 1000;
      return ;
    }
  get_current_time(&current);
  if ((*ptr)->time.tv_usec - current.tv_usec < 0)
    time->tv_usec = 0;
  else
    time->tv_usec = (*ptr)->time.tv_usec - current.tv_usec;
  if ((*ptr)->time.tv_sec - current.tv_sec < 0)
    time->tv_sec = 0;
  else
    time->tv_sec = (*ptr)->time.tv_sec - current.tv_sec;
  // or first finish incant or first player dead (with a sort)
}

static void set_timeout_death(t_data_serv ds, t_timeval time)
{
  double tot;
  t_player *ptr = list_front(ds->player);

  if (!ptr)
    {
      time->tv_usec = 1000;
      time->tv_sec = 1000;
      return ;
    }
  if ((*ptr)->inv.resources[FOOD] <= 0)
    {
      time->tv_usec = 0;
      time->tv_sec = 0;
      return ;
    }
  tot = ((*ptr)->inv.resources[FOOD] - 1) * 127;
  tot += (*ptr)->inv.cur_life;
  tot *= 1 / ds->t;
  tot *= 1000000;
  time->tv_usec = (int)tot / 1000000;
  time->tv_sec = (int)tot % 1000000;
}

static void set_timeout_incant(t_player *ptr, t_timeval time)
{
  (void)ptr;
  (void)time;
}

void	set_timeout_select(t_data_serv ds, t_timeval time)
{
  t_u_timeval death;

  set_timeout_action(list_front(&(ds->action->queue)), time);
  set_timeout_death(ds, &death);
  if (cmp_time(time, &death) > 0)
    {
      time->tv_usec = death.tv_usec;
      time->tv_sec = death.tv_sec;
    }
}
