/*
 * Fiahil
 * 06.06.2012
 */

#ifndef __NETWORK_H__
#define __NETWORK_H__

int	set_connection(int);
int	get_server_fd();
int	accept_connection(t_sockLayer);
char	*my_receive(int);
int	my_send(int, char*);

#endif /* __NETWORK_H__ */
