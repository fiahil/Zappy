/*
 * Fiahil
 * 06.06.2012
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "def.h"
#include "iter.h"
#include "clock.h"
#include "network.h"
#include "cmd_parse.h"
#include "msgout_cmd.h"
#include "handle_error.h"
#include "iter_function.h"
#include "select_manager.h"
#include "server_routine.h"

static t_select_manager		g_sm = 0;
static t_data_serv		g_ds = 0;

static void	iter_rds(void *ptr, size_t s)
{
  (void)s;
  if (select_isset(g_sm, (*(t_player*)ptr)->cm.sock.fd)
      && (*(t_player*)ptr)->cm.online)
    server_routine_input(g_ds, *(t_player*)ptr);
}

static void	iter_out(void *ptr, size_t s)
{
  (void)s;
  server_routine_output(g_ds, *(t_player*)ptr);
}

static void	push_new_action(t_player_action pa)
{
  int			off;
  t_proc_func		ret;
  t_player_action	act;

  off = -1;
  ret = NULL;
  while (!(pa->player->cm.in->empty) && !ret)
    {
      if (!(ret = cmd_parse(list_front(pa->player->cm.in), &off)))
	msgout_fail(pa->player->cm.out);
      else
	{
	  if (!(act = malloc(sizeof(*act))))
	    exit(1); // TODO retour d'erreur
	  act->action = ret;
	  act->done = FALSE;
	  get_time_per_function(&(act->time), ret, g_ds->t);
	  act->player = pa->player;
	  act->param = strdup(list_front(pa->player->cm.in) + off);
	  pqueue_push(g_ds->action, &(act), sizeof(&act));
	  pa->player->cm.is_processing = TRUE;
	}
      list_pop_front(pa->player->cm.in);
    }
}

static void	iter_action(void *ptr, size_t s)
{
  (void)s;
  t_u_timeval current;

  get_current_time(&current);
  if ((*((t_player_action*)ptr))->player->cm.is_processing
      && !((*((t_player_action*)ptr))->done)
      && cmp_time(&current, &((*((t_player_action*)ptr))->time)) == 1)
    {
      ((*((t_player_action*)ptr))->action)
	((*((t_player_action*)ptr))->player, (*((t_player_action*)ptr))->param, g_ds);
      (*((t_player_action*)ptr))->done = TRUE;
      (*((t_player_action*)ptr))->player->cm.is_processing = FALSE;
    }
	if (!(*((t_player_action*)ptr))->player->cm.in->empty
	    && !((*((t_player_action*)ptr))->player->cm.is_processing))
    {
      printf("Processing \"%s\" ... \n",
	     (char*)(list_front((*((t_player_action*)ptr))->player->cm.in))); // TODO affichage tmp
      fflush(0);
      push_new_action(*((t_player_action*)ptr)); // TODO PARAMETRE
    }
}

void		iter_client(t_select_manager sm, t_data_serv ds)
{
  t_player	player;

  g_sm = sm;
  g_ds = ds;
  select_manager(ds, sm);
  if (select_isset(sm, ds->sock.fd))
    {
      player = init_player();
      if (accept_connection(sm, ds, player) < 0)
	free(player);
      else
	list_push_back_new(ds->player, &player, sizeof(&player));
    }
  list_for_each(ds->player, &iter_rds);
  list_for_each(&(ds->action->queue), &iter_action);
  list_remove_if(&(ds->action->queue), &action_cleaner);
  list_for_each(ds->player, &iter_out);
  set_timeout_select(list_front(&(ds->action->queue)), &(sm->timeout));
}
