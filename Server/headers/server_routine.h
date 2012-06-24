/*
** server_routine.h for zappy_bibicy* in /home/lefevr_u/GIT/zappy/Zappy/Server/headers
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:19:10 2012 ulric lefevre
** Last update Sat Jun 23 20:19:12 2012 ulric lefevre
*/

#ifndef __SERVER_ROUTINE_H__
#define __SERVER_ROUTINE_H__

#include "def.h"

void	server_routine_input(t_data_serv, t_player);
void	server_routine_output(t_data_serv, t_player);
t_bool  welcome_player(t_data_serv, t_player, char *);

#endif /* __SERVER_ROUTINE_H__ */
