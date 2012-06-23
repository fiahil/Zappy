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
#include "incant.h"
#include "player.h"
#include "network.h"
#include "algorithm.h"
#include "cmd_parse.h"
#include "msgout_cmd.h"
#include "func_cleaner.h"
#include "handle_error.h"
#include "team_manager.h"
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
  if ((*(t_player*)ptr)->cm.online && (*(t_player*)ptr)->dead == FALSE
      && select_r_isset(g_sm, (*(t_player*)ptr)->cm.sock.fd))
    server_routine_input(g_ds, *(t_player*)ptr);
  if ((*(t_player*)ptr)->cm.online && (*(t_player*)ptr)->deleted == FALSE
      && select_w_isset(g_sm, (*(t_player*)ptr)->cm.sock.fd))
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
  t_u_timeval current;

  (void)s;
  get_current_time(&current);
  if (((t_player_action)ptr)->player->cm.is_processing
      && !(((t_player_action)ptr)->done)
      && cmp_time(&current, &(((t_player_action)ptr)->time)) == 1)
    {
      if (((t_player_action)ptr)->player->dead == FALSE)
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

static void	iter_egg(void *ptr, size_t s)
{
  t_iter	*it;
  t_u_timeval	current;

  (void)s;
  get_current_time(&current);
  if (cmp_time(&current, &(((t_egg)ptr)->timeout)) >= 0)
    {
      // il ne rentre pas ici ??
      printf("New player !\n");
      it = list_find_cmp(g_ds->teams, &func_cmp_team, ((t_egg)ptr)->fetus->team, 0);
      ((t_team)it->data)->remaining += 1;
      list_push_back_new(g_ds->player, &((t_egg)ptr)->fetus,
			 sizeof(((t_egg)ptr)->fetus));
      ((t_egg)ptr)->timeout.tv_sec = 0;
    }
}

static void		iter_incant(void *ptr, size_t s)
{
  t_u_timeval	current;

  (void)s;
  get_current_time(&current);
  if (cmp_time(&((t_incant)ptr)->timeout, &current) <= 0)
    {
      if (incant_is_ok((t_incant)ptr))
	level_up((t_incant)ptr);
      else
	printf("Incant couldn't be performed\n");
      //msgout_incantation(((t_incant)ptr)->incantor->cm.out, ((t_incant)ptr)->incantor->lvl);
      ((t_incant)ptr)->timeout.tv_sec = 0;
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
	list_push_back_new(ds->player, &player, sizeof(player));
    }
  list_for_each(ds->player, &iter_rds);
  list_for_each(&(ds->action->queue), &iter_action);
  list_remove_if(&(ds->action->queue), &action_cleaner);
  list_for_each(&(ds->incant->queue), &iter_incant);
  list_remove_if(&(ds->incant->queue), &incant_cleaner);
  list_for_each(ds->egg, &iter_egg);
  list_remove_if(ds->egg, &egg_cleaner);
  list_sort(ds->player, &sort_player_life);
  list_remove_if(ds->player, &player_cleaner);
  g_last.tv_sec = g_current.tv_sec;
  g_last.tv_usec = g_current.tv_usec;
  set_timeout_select(ds, &(sm->timeout));
}
