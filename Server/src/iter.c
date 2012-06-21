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
#include "player.h"
#include "network.h"
#include "algorithm.h"
#include "cmd_parse.h"
#include "msgout_cmd.h"
#include "handle_error.h"
#include "iter_function.h"
#include "select_manager.h"
#include "server_routine.h"

static t_select_manager		g_sm = 0;
static t_data_serv		g_ds = 0;
static t_u_timeval		g_last = {0, 0};
static t_u_timeval		g_current = {0, 0};

static void	iter_rds(void *ptr, size_t s)
{
  (void)s;
  if (select_r_isset(g_sm, (*(t_player*)ptr)->cm.sock.fd) &&
      (*(t_player*)ptr)->cm.online)
    server_routine_input(g_ds, *(t_player*)ptr);
  if (select_w_isset(g_sm, (*(t_player*)ptr)->cm.sock.fd) &&
      (*(t_player*)ptr)->cm.online)
    server_routine_output(g_ds, *(t_player*)ptr);
}

static void	push_new_action(t_player_action pa)
{
  int			off;
  t_proc_func		ret;
  t_u_player_action	act;

  off = -1;
  ret = NULL;
  while (!(pa->player->cm.in->empty) && !ret)
    {
      if (!(ret = cmd_parse(list_front(pa->player->cm.in), &off)))
	msgout_fail(pa->player->cm.out);
      else
	{
	  //if (!(act = malloc(sizeof(*act))))
	  //exit(1); // TODO retour d'erreur
	  act.action = ret;
	  act.done = FALSE;
	  get_time_per_function(&(act.time), ret, g_ds->t);
	  act.player = pa->player;
	  act.param = strdup(list_front(pa->player->cm.in) + off);
	  pqueue_push(g_ds->action, &act, sizeof(act));
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
  if (((t_player_action)ptr)->player->cm.is_processing
      && !(((t_player_action)ptr)->done)
      && cmp_time(&current, &(((t_player_action)ptr)->time)) == 1)
    {
      (((t_player_action)ptr)->action)
	(((t_player_action)ptr)->player, ((t_player_action)ptr)->param, g_ds);
      ((t_player_action)ptr)->done = TRUE;
      ((t_player_action)ptr)->player->cm.is_processing = FALSE;
    }
	if (!((t_player_action)ptr)->player->cm.in->empty
	    && !(((t_player_action)ptr)->player->cm.is_processing))
    {
      printf("Processing \"%s\" ... \n",
	     (char*)(list_front(((t_player_action)ptr)->player->cm.in))); // TODO affichage tmp
      fflush(0);
      push_new_action((t_player_action)ptr); // TODO PARAMETRE
    }
}

static void		iter_lose_life(void *ptr, size_t s)
{
  double	val;
  int		dmg;
  int		i;

  (void)s;
  i = 0;
  val = g_current.tv_usec - g_last.tv_usec;
  val += ((g_current.tv_sec - g_last.tv_sec) * 1000000.0);
  val /= 1000000.0;
  val /= (1.0 / g_ds->t);
  dmg = val;
  while (!i)
    if (dmg < (*(t_player*)ptr)->inv.cur_life)
      {
	(*(t_player*)ptr)->inv.cur_life -= dmg;
	i = 1;
      }
    else
      {
	dmg -= (*(t_player*)ptr)->inv.cur_life;
	(*(t_player*)ptr)->inv.cur_life = 127;
	(*(t_player*)ptr)->inv.resources[FOOD] -= 1;
      }
  if ((*(t_player*)ptr)->inv.resources[FOOD] <= 0)
    {
      (*(t_player*)ptr)->dead = TRUE;
      msgout_mort((*(t_player*)ptr)->cm.out);
    }
}

void		iter_client(t_select_manager sm, t_data_serv ds)
{
  t_player	player;

  g_sm = sm;
  g_ds = ds;
  select_manager(ds, sm);
  get_current_time(&g_current);
  if ((g_last.tv_sec) || (g_last.tv_usec))
    list_for_each(ds->player, &iter_lose_life);
  if (select_r_isset(sm, ds->sock.fd))
    {
      player = create_player();
      if (accept_connection(sm, ds, player) < 0)
	delete_player(player);
      else
	list_push_back_new(ds->player, &player, sizeof(&player));
    }
  list_for_each(ds->player, &iter_rds);
  list_for_each(&(ds->action->queue), &iter_action);
  list_remove_if(&(ds->action->queue), &action_cleaner);
  // Incantation loop here
  list_sort(ds->player, &sort_player_life);
  g_last.tv_sec = g_current.tv_sec;
  g_last.tv_usec = g_current.tv_usec;
  set_timeout_select(ds, &(sm->timeout));
}
