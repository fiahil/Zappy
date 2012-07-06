/*
** func_cmp.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:49:18 2012 ulric lefevre
** Last update Fri Jul  6 15:54:59 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"

char		cmp_time(t_timeval fst, t_timeval scd)
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

int		cmp_team(void *s1, size_t s1len, void *s2, size_t s2len)
{
  (void)s1len;
  (void)s2len;
  return (strcmp(((t_team)s1)->name, (char*)s2));
}

int		cmp_incant(void *e1, size_t s1, void *e2, size_t s2)
{
  (void)s1;
  (void)s2;
  return (cmp_time(&(((t_incant)e1)->timeout),
		   &(((t_incant)e2)->timeout)));
}

int		cmp_action(void *e1, size_t s1, void *e2, size_t s2)
{
  (void)s1;
  (void)s2;
  return (cmp_time(&((t_player_action)e1)->time,
		   &((t_player_action)e2)->time));
}
