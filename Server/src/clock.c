/*
** clock.c for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/src/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on Tue Jun 12 16:11:14 2012 benjamin businaro
*/

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "handle_error.h"
#include "clock.h"

void	get_current_time(t_timeval time)
{
  struct timezone	zone;

  zone.tz_minuteswest = 0;
  zone.tz_dsttime = 0;
  gettimeofday(time, &zone);
}

char	cmp_time(t_timeval fst, t_timeval scd)
{
  if (fst->tv_sec > scd->tv_sec)
    return (1);
  if (fst->tv_sec < scd->tv_sec)
    return (-1);
  if (fst->tv_usec > scd->tv_usec)
    return (1);
  if (fst->tv_usec < scd->tv_usec)
    return (-1);
  return (0);
}

void	add_time(t_timeval time, double maj, double t)
{
  maj /= t;
  maj *= 1000000;
  time->tv_sec += (int)(maj) / 1000000;
  time->tv_usec += (int)(maj) % 1000000;
}


void	unitest_clock()
{
  t_u_timeval time;
  t_u_timeval time2;

  get_current_time(&time);
  sleep(1);
  get_current_time(&time2);
  puts(".:::: Unitest clock.c ::::.\n");
  puts(".:: value ::.");
  printf("# t1 sec = %d, usec = %d\n", (int)time.tv_sec, (int)time.tv_usec);
  printf("# t2 sec = %d, usec = %d\n", (int)time2.tv_sec, (int)time2.tv_usec);
  puts(".:: cmp_time ::.");
  printf("# cmp t1 and t2 : %d, expected : -1\n", (int)cmp_time(&time, &time2));
  printf("# cmp t2 and t1 : %d, expected : 1\n", (int)cmp_time(&time2, &time));
  printf("# cmp t1 and t1 : %d, expected : 0\n", (int)cmp_time(&time, &time));
  puts(".:: add_time ::.");
  add_time(&time, 7, 300);
  printf("# add t1 [7] [300] : sec = %d, usec = %d\n", (int)time.tv_sec, (int)time.tv_usec);
}
