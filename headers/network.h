/*
 * Fiahil
 * 06.06.2012
 */

#ifndef __NETWORK_H__
#define __NETWORK_H__

int	set_connection(int);
int	my_receive(t_sockLayer, char*);
int	my_send(t_sockLayer, char*);

#endif /* __NETWORK_H__ */
