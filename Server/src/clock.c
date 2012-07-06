/*
** clock.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:17:14 2012 ulric lefevre
** Last update Fri Jul  6 16:38:30 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"clock.h"
#include	"process_function.h"

static const t_u_time_attrib g_time_attrib[] =
  {
    {&move_process, 7.0},
    {&right_process, 7.0},
    {&left_process, 7.0},
    {&look_process, 7.0},
    {&inventory_process, 7.0},
    {&take_process, 7.0},
    {&drop_process, 7.0},
    {&expulse_process, 7.0},
    {&broadcast_process, 7.0},
    {&incantation_process, 300.0},
    {&fork_process, 42.0},
    {&connect_nbr_process, 0.0},
    {NULL, 0}
  };

void		get_current_time(t_timeval time)
{
  t_u_timezone	zone;

  zone.tz_minuteswest = 0;
  zone.tz_dsttime = 0;
  gettimeofday(time, &zone);
}

void		get_time_per_function(t_timeval time, t_proc_func f, double t)
{
  int		i;

  i = 0;
  get_current_time(time);
  while (g_time_attrib[i].func)
    {
      if (g_time_attrib[i].func == f)
	add_time(time, g_time_attrib[i].timer, t);
      ++i;
    }
}

void		add_time(t_timeval time, double maj, double t)
{
  if (t)
    maj /= t;
  maj *= 1000000;
  time->tv_sec += (int)maj / 1000000;
  time->tv_usec += (int)maj % 1000000;
}

double		convert_to_u(t_timeval time)
{
  double	ret;

  ret = time->tv_sec * 1000000;
  ret += time->tv_usec;
  return (ret);
}
