/*
** clock.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/headers
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:21:47 2012 ulric lefevre
** Last update Fri Jul  6 16:06:00 2012 ulric lefevre
*/

#ifndef		__CLOCK_H__
# define	__CLOCK_H__

#include	"def.h"

void	get_current_time(t_timeval);
char	cmp_time(t_timeval, t_timeval);
void	get_time_per_function(t_timeval, t_proc_func, double);
void	add_time(t_timeval, double, double);
void	unitest_clock();
double	convert_to_u(t_timeval);

#endif		/* __CLOCK_H__ */

