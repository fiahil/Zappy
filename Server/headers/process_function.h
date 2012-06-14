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

t_bool	move_process_function(t_clientManager, char *);
t_bool	right_process_function(t_clientManager, char *);
t_bool	left_process_function(t_clientManager, char *);
t_bool	look_process_function(t_clientManager, char *);
t_bool	inventory_process_function(t_clientManager, char *);
t_bool	take_process_function(t_clientManager, char *);
t_bool	drop_process_function(t_clientManager, char *);
t_bool	expulse_process_function(t_clientManager, char *);
t_bool	broadcast_process_function(t_clientManager, char *);
t_bool	incantation_process_function(t_clientManager, char *);
t_bool	fork_process_function(t_clientManager, char *);
t_bool	connect_nbr_process_function(t_clientManager, char *);

#endif /* __PROCESS_FUNCTION_H__ */

