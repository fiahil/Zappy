/*
** process_function.h for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/src/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on  Thu Jun  7 14:18:11 2012 benjamin businaro
*/

#ifndef __PROCESS_FUNCTION_H__
#define __PROCESS_FUNCTION_H__

#include "def.h"

t_bool	move_process(t_player, char *, t_data_serv);
t_bool	right_process(t_player, char *, t_data_serv);
t_bool	left_process(t_player, char *, t_data_serv);
t_bool	look_process(t_player, char *, t_data_serv);
t_bool	inventory_process(t_player, char *, t_data_serv);
t_bool	take_process(t_player, char *, t_data_serv);
t_bool	drop_process(t_player, char *, t_data_serv);
t_bool	expulse_process(t_player, char *, t_data_serv);
t_bool	broadcast_process(t_player, char *, t_data_serv);
t_bool	incantation_process(t_player, char *, t_data_serv);
t_bool	fork_process(t_player, char *, t_data_serv);
t_bool	connect_nbr_process(t_player, char *, t_data_serv);
char	*get_look(t_player, t_map);
void	message(t_player, t_player, char*);

#endif /* __PROCESS_FUNCTION_H__ */

