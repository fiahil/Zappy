/*
** clock.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:17:14 2012 ulric lefevre
** Last update Fri Jul  6 16:20:15 2012 ulric lefevre
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

void		unitest_clock()
{
  // TODO fonction d'affichage tmp
  t_u_timeval	time;
  t_u_timeval	time2;

  get_current_time(&time);
  sleep(1);
  get_current_time(&time2);
  puts(".:::: Unitest clock.c ::::.\n");
  puts(".:: value ::.");
  printf("# t1 sec = %d, usec = %d\n", (int)time.tv_sec, (int)time.tv_usec);
  printf("# t2 sec = %d, usec = %d\n", (int)time2.tv_sec, (int)time2.tv_usec);
  puts(".:: cmp_time ::.");
  printf("# cmp t1 and t2 : %d, expected : -1\n",
	 (int)cmp_time(&time, &time2));
  printf("# cmp t2 and t1 : %d, expected : 1\n",
	 (int)cmp_time(&time2, &time));
  printf("# cmp t1 and t1 : %d, expected : 0\n",
	 (int)cmp_time(&time, &time));
  puts(".:: get_time_per_function ::.");
  get_time_per_function(&time2, &move_process, 300);
  printf("# get t2 move [300] : sec = %d, usec = %d\n",
	 (int)time2.tv_sec, (int)time2.tv_usec);
  puts(".:: add_time ::.");
  add_time(&time, 7, 300);
  printf("# add t1 [7] [300] : sec = %d, usec = %d\n",
	 (int)time.tv_sec, (int)time.tv_usec);
}
