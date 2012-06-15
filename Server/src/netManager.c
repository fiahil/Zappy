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

void		iter_client(t_select_manager sm, t_data_serv data_serv)
{
  //t_player	player;

  select_manager(data_serv, sm);/*
  while (++i < n)
    if (!epoll->ev[i].data.ptr)
      { //TODO WIP Fonction create_player
	if (!(player = malloc(sizeof(t_u_player))))
	  handleError("malloc", strerror(errno), -1);
	player->lvl = 1;
	player->team = "poney";
	player->pos.x = 0;
	player->pos.y = 0;
	player->dir = NORTH;
	player->dead = FALSE;
	player->welcome = FALSE;
	memset(player->cm.stock, '\0', sizeof(player->cm.stock));
	player->cm.in = new_list(NULL, NULL, NULL);
	player->cm.out = new_list(NULL, NULL, NULL);
	player->cm.mode = UNKNOW;
	player->cm.is_processing = FALSE;
	player->cm.online = FALSE;
	if (accept_connection(epoll, data_serv, player) < 0)
	  free(player);
      }
    else
      if (epoll->ev[i].events & EPOLLIN)
	server_routine_input(data_serv, epoll->ev[i].data.ptr);
      else if (epoll->ev[i].events & EPOLLOUT)
	server_routine_output(data_serv, epoll->ev[i].data.ptr);
	*/
}
