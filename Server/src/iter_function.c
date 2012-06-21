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
#include <stdio.h>

#include "handle_error.h"
#include "iter_function.h"
#include "map.h"
#include "clock.h"
#include "player.h"

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

static void	set_timeout_action(t_player_action ptr, t_timeval time)
{
  t_u_timeval	current;
  double	d_current;
  double	d_act;

  if (!ptr)
    {
      time->tv_usec = 10000;
      time->tv_sec = 10000;
      return ;
    }
  get_current_time(&current);
  d_current = convert_to_u(&current);
  d_act = convert_to_u(&(ptr->time));
  if (d_act - d_current <= 0)
    {
      time->tv_usec = 0;
      time->tv_sec = 0;
    }
  else
    {
      time->tv_usec = (int)(d_act - d_current) % 1000000;
      time->tv_sec = (int)(d_act - d_current) / 1000000;
    }
}

static void set_timeout_death(t_data_serv ds, t_timeval time)
{
  double tot;
  t_player *ptr = list_front(ds->player);

  if (!ptr)
    {
      time->tv_usec = 10000;
      time->tv_sec = 10000;
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
  tot *= 1.0 / ds->t;
  tot *= 1000000.0;
  time->tv_sec = (int)tot / 1000000;
  time->tv_usec = (int)tot % 1000000;
}

/* static void set_timeout_incant(t_player *ptr, t_timeval time) */
/* { */
/*   (void)ptr; */
/*   (void)time; */
/* } */

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
