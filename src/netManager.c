/*
 * Fiahil
 * 06.06.2012
 */

#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "netManager.h"
#include "network.h"
#include "server_routine.h"
#include "select_manager.h"
#include "epoll_manager.h"
#include "handle_error.h"

static t_clientManager		*clientTab = NULL; // TODO
static size_t			g_index = 0;

int		initClientTab(void)
{
  int		i;
  void		*batAlloc;

  i = 0;
  clientTab = malloc(((DEFAULT_TAB + 1) * sizeof(t_clientManager)));
  batAlloc = malloc((DEFAULT_TAB + 1) * sizeof(t_u_clientManager));
  if (!clientTab || !batAlloc)
    return (0);
  while (i < DEFAULT_TAB)
  {
    clientTab[i] = batAlloc;
    clientTab[i]->online = FALSE;
    clientTab[i]->mode = LF;
    clientTab[i]->dead = FALSE;
    clientTab[i]->in = new_list(NULL, NULL, NULL);
    clientTab[i]->out = new_list(NULL, NULL, NULL);
    memset(clientTab[i]->stock, '\0', sizeof(clientTab[i]->stock));
    clientTab[i]->sock = malloc(sizeof(t_u_sockLayer));
    if (!clientTab[i]->sock)
      return (0);
    batAlloc += sizeof(t_u_clientManager);
    ++i;
  }
  clientTab[i] = NULL;
  return (1);
}

void	iter_client(t_epoll_manager epoll)
{
  int			n;
  int			i;

  i = -1;
  n = update_monitor(epoll);
  while (++i < n)
    if (!epoll->ev[i].data.ptr)
      {
	if (accept_connection(epoll, clientTab[g_index]) > -1)
	  clientTab[g_index++]->online = TRUE;
      }
    else
      if (epoll->ev[i].events & EPOLLIN)
	server_routine_input(epoll->ev[i].data.ptr);
      else if (epoll->ev[i].events & EPOLLOUT)
	server_routine_output(epoll->ev[i].data.ptr);
}
