/*
** clock.h for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/Server/headers/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on  Wed Jun 13 11:39:01 2012 benjamin businaro
** Last update Thu Jun 14 14:13:46 2012 benjamin businaro
*/

#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "def.h"

void	get_current_time(t_timeval);
char	cmp_time(t_timeval, t_timeval);
void	get_time_per_function(t_timeval, procFunc, double);
void	add_time(t_timeval, double, double);
void	unitest_clock();

#endif /* __CLOCK_H__ */
