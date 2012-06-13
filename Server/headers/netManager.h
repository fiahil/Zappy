/*
 * Fiahil
 * 06.06.2012
 */

#ifndef __NETMANAGER_H__
#define __NETMANAGER_H__

#define DEFAULT_TAB	(512)

#include "def.h"

int	initClientTab(void);
void	iter_client(t_epoll_manager);

#endif /* __NETMANAGER_H__ */
