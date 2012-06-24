/*
** network.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/headers
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:19:33 2012 ulric lefevre
** Last update Sat Jun 23 20:21:53 2012 ulric lefevre
*/

#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "def.h"

int	set_connection(t_data_serv, int);
int	accept_connection(t_select_manager, t_data_serv, t_player);
char	*my_receive(int);
int	my_send(int, char*);

#endif /* __NETWORK_H__ */
