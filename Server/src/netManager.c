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
#include "map.h"

//static t_clientManager		*clientTab = NULL; // TODO
//static size_t			g_index = 0;

/*
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
    clientTab[i]->mode = UNKNOW;
    clientTab[i]->is_processing = FALSE;
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
*/

void		iter_client(t_epoll_manager epoll, t_data_serv data_serv)
{
  int		n;
  int		i;
  t_player	p;

  i = -1;
  n = update_monitor(epoll);
  while (++i < n)
    if (!epoll->ev[i].data.ptr)
      { //TODO WIP Fonction create_player
	if (!(p = malloc(sizeof(t_u_player))))
	  handleError("malloc", strerror(errno), -1);
	p->lvl = 1;
	p->team = "poney";
	p->pos.x = 0;
	p->pos.y = 0;
	list_push_back_new(&(get_map(NULL)->map[p->pos.y][p->pos.x]->players),
			   &p, sizeof(&p));
	// TODO : placer le joueur dans la map
	p->dir = NORTH;
	p->dead = FALSE;
	p->welcome = FALSE;
	memset(p->cm.stock, '\0', sizeof(p->cm.stock));
	p->cm.in = new_list(NULL, NULL, NULL);
	p->cm.out = new_list(NULL, NULL, NULL);
	p->cm.mode = UNKNOW;
	p->cm.is_processing = FALSE;
	p->cm.online = FALSE;
	if (accept_connection(epoll, data_serv, p) < 0)
	  free(p);
      }
    else
      if (epoll->ev[i].events & EPOLLIN)
	server_routine_input(data_serv, epoll->ev[i].data.ptr);
      else if (epoll->ev[i].events & EPOLLOUT)
	server_routine_output(data_serv, epoll->ev[i].data.ptr);
}
