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
#include "handle_error.h"

static t_select_manager		g_sm = 0;
static t_data_serv		g_ds = 0;

static void	iter_rds(void *ptr, size_t s)
{
  (void)s;
  if (select_isset(g_sm, (*(t_player*)ptr)->cm.sock.fd) && (*(t_player*)ptr)->cm.online)
    server_routine_input(g_ds, *(t_player*)ptr);
}

void		iter_client(t_select_manager sm, t_data_serv ds)
{
  t_player	player;
  
  g_sm = sm;
  g_ds = ds;
  select_manager(ds, sm);
  if (select_isset(sm, ds->sock.fd))
  {
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
    if (accept_connection(sm, ds, player) < 0)
      free(player);
    else
      list_push_back_new(ds->player, &player, sizeof(&player));
  }
  list_for_each(ds->player, &iter_rds);
}
