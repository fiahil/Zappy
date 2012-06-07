/*
 * Fiahil
 * 06.06.2012
 */

#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "netManager.h"
#include "server_routine.h"
#include "select_manager.h"

static t_clientManager		*clientTab = NULL;

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
    memset(clientTab[i]->stock, '\0', sizeof(clientTab[i]->stock));
    clientTab[i]->sock = malloc(sizeof(t_u_sockLayer));
    if (!clientTab[i]->sock)
      return (0);
    clientTab[i]->sock->addr = NULL;
    batAlloc += sizeof(t_u_clientManager);
    ++i;
  }
  clientTab[i] = NULL;
  return (1);
}

int		iterClient(void)
{
  int		i;

  select_manager(clientTab);
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
