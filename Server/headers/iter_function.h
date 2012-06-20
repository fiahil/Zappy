/*
** iter_function.h for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/Server/headers/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on  Sat Jun 16 16:16:43 2012 benjamin businaro
** Last update Tue Jun 19 17:41:02 2012 benjamin businaro
*/

#ifndef __ITER_FUNCTION_H__
#define __ITER_FUNCTION_H__

#include "def.h"

int		action_cleaner(void *, size_t );
t_player	init_player();
int	sort_player_life(void *, size_t, void *, size_t);
void	set_timeout_select(t_data_serv, t_timeval);

#endif /* __ITER_FUNCTION_H__ */

