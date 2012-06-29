/*
** set_timeout.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:13:54 2012 ulric lefevre
** Last update Fri Jun 29 13:05:35 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"clock.h"

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
      time->tv_usec = 5;
      time->tv_sec = 0;
    }
  else
    {
      time->tv_usec = (int)(d_act - d_current) % 1000000;
      time->tv_sec = (int)(d_act - d_current) / 1000000;
    }
}

static void	set_timeout_death(t_data_serv ds, t_timeval time)
{
  double	tot;
  t_player	*ptr;

  ptr = list_front(ds->player);
  if (!ptr)
    {
      time->tv_usec = 10000;
      time->tv_sec = 10000;
      return ;
    }
  if ((*ptr)->inv.resources[FOOD] <= 0)
    {
      time->tv_usec = 5;
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

void		set_timeout_select(t_data_serv ds, t_timeval time)
{
  t_u_timeval	death;
  t_u_timeval	incant;

  set_timeout_action(list_front(&(ds->action->queue)), time);
  set_timeout_death(ds, &death);
  if (cmp_time(time, &death) > 0)
    {
      time->tv_usec = death.tv_usec;
      time->tv_sec = death.tv_sec;
    }
  if (cmp_time(time, &incant) > 0)
    {
      time->tv_usec = incant.tv_usec;
      time->tv_sec = incant.tv_sec;
    }
}
