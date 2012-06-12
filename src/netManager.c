/*
 * Fiahil
 * 06.06.2012
 */

#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "netManager.h"
#include "network.h"
#include "server_routine.h"
#include "select_manager.h"

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
    init_list(clientTab[i]->in, NULL, NULL, NULL);
    init_list(clientTab[i]->out, NULL, NULL, NULL);
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

int		iterClient(void)
{
  int		i;

  select_manager(clientTab, get_server_fd());
  if (select_isset(get_server_fd(), READ))
    {
      accept_connection(clientTab[g_index]->sock);
      clientTab[g_index++]->online = TRUE;
    }
  i = 0;
  while (clientTab[i])
    {
      if (clientTab[i]->online)
	{
	  if (select_isset(clientTab[i]->sock->fd, READ))
	    server_routine_input(clientTab[i]);
	  if (select_isset(clientTab[i]->sock->fd, WRITE))
	    server_routine_output(clientTab[i]);
	}
      ++i;
    }
  return (0);
}
