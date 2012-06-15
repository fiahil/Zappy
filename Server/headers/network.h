/*
 * Fiahil
 * 06.06.2012
 */

#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "def.h"

int	set_connection(t_data_serv, int);
int	accept_connection(t_select_manager, t_data_serv, t_player);
char	*my_receive(int);
int	my_send(int, char*);

#endif /* __NETWORK_H__ */
