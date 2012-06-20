/*
 * Fiahil
 * 07.06.2012
 */

#ifndef __SERVER_ROUTINE_H__
#define __SERVER_ROUTINE_H__

#include "def.h"

void	server_routine_input(t_data_serv, t_player);
void	server_routine_output(t_data_serv, t_player);
t_bool  welcome_player(t_data_serv, t_player, char *);

#endif /* __SERVER_ROUTINE_H__ */
