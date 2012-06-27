/*
** iter.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:50 2012 ulric lefevre
** Last update Tue Jun 26 17:54:10 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"iter.h"
#include	"clock.h"
#include	"player.h"
#include	"stdout.h"
#include	"network.h"
#include	"graphic.h"
#include	"algorithm.h"
#include	"iter_tools.h"
#include	"msgout_cmd.h"
#include	"set_timeout.h"
#include	"var_manager.h"
#include	"func_cleaner.h"
#include	"iter_function.h"
#include	"select_manager.h"

static t_u_timeval	g_last = {0, 0};
static t_u_timeval	g_current = {0, 0};

static int		get_dmg()
{
  t_data_serv	ds;
  double	val;

  ds = get_data_serv(NULL);
  val = g_current.tv_usec - g_last.tv_usec;
  val += ((g_current.tv_sec - g_last.tv_sec) * 1000000.0);
  val /= 1000000.0;
  val /= (1.0 / ds->t);
  return (val);
}

static void		lose_life_loop(t_player *this)
{
  int		dmg;
  int		i;

  i = 0;
  dmg = get_dmg();
  while (!i)
    {
      if (dmg < (*this)->inv.cur_life)
	{
	  (*this)->inv.cur_life -= dmg;
	  i = 1;
	}
      else
	{
	  dmg -= (*this)->inv.cur_life;
	  (*this)->inv.cur_life = 127;
	  (*this)->inv.resources[FOOD] -= 1;
	}
    }
}

static void		iter_lose_life(void *ptr, size_t s)
{
  (void)s;
  if ((*(t_player*)ptr)->welcome)
    {
      lose_life_loop((t_player*)ptr);
      if ((*(t_player*)ptr)->inv.resources[FOOD] <= 0)
	{
	  (*(t_player*)ptr)->dead = TRUE;
	  msgout_mort((*(t_player*)ptr));
	}
    }
}

static void	iter_lists(t_data_serv ds)
{
  list_for_each(ds->player, &iter_rds);
  list_for_each(&(ds->action->queue), &iter_action);
  list_remove_if(&(ds->action->queue), &action_cleaner);
  list_for_each(&(ds->incant->queue), &iter_incant);
  list_remove_if(&(ds->incant->queue), &incant_cleaner);
  list_for_each(ds->egg, &iter_egg);
  list_remove_if(ds->egg, &egg_cleaner);
  list_sort(ds->player, &sort_player_life);
  list_remove_if(ds->player, &player_cleaner);
  mn_out(ds->monitor);
}

void		iter_client()
{
  t_player		player;
  t_select_manager	sm;
  t_data_serv		ds;

  sm = get_select_manager(NULL);
  ds = get_data_serv(NULL);
  select_manager(ds, sm);
  get_current_time(&g_current);
  if ((g_last.tv_sec) || (g_last.tv_usec))
    list_for_each(ds->player, &iter_lose_life);
  if (select_r_isset(sm, ds->sock.fd))
    {
      player = create_player(-1);
      if (player && accept_connection(sm, ds, player) < 0)
	delete_player(player);
      else if (player)
	list_push_back_new(ds->player, &player, sizeof(player));
    }
  iter_lists(ds);
  g_last.tv_sec = g_current.tv_sec;
  g_last.tv_usec = g_current.tv_usec;
  set_timeout_select(ds, &(sm->timeout));
}
