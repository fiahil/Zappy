/*
 * Fiahil
 * 06.06.2012
 */

#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "netManager.h"

static t_clientManager		*clientTab = NULL;

int		initClientTab(void)
{
  int		i;
  void		*batAlloc;

  i = 0;
  clientTab = malloc((DEFAULT_TAB * sizeof(t_clientManager)) + 1);
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

  selectManager(clientTab);
  i = 0;
  while (clientTab[i])
  {
    if (clientTab[i]->online)
    {
      if (selectIsset(clientTab[i]->sock->fd, READ))
	; //SERVER_ROUTINE_INPUT(clientTab[i]); 
      if (selectIsset(clientTab[i]->sock->fd, WRITE))
	; //SERVER_ROUTINE_OUTPUT(clientTab[i])
    }
    ++i;
  }
}
