/*
** iter_tools.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:41 2012 ulric lefevre
** Last update Tue Jul 10 22:58:15 2012 ulric lefevre
*/

#include	<errno.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"map.h"
#include	"clock.h"
#include	"player.h"
#include	"cmd_parse.h"
#include	"iter_tools.h"
#include	"msgout_cmd.h"
#include	"res_manager.h"
#include	"var_manager.h"
#include	"handle_error.h"
#include	"iter_function.h"
#include	"process_function.h"

int		sort_player_life(void *ptr1, size_t sz1, void *ptr2, size_t sz2)
{
  int		val1;
  int		val2;

  (void)sz1;
  (void)sz2;
  val1 = 0;
  val2 = 0;
  if ((*((t_player*)(ptr1)))->inv.resources[FOOD] <= 0)
    val1 = ((*((t_player*)(ptr1)))->inv.resources[FOOD] - 1)
      * 127 + (*((t_player*)(ptr1)))->inv.cur_life;
  if ((*((t_player*)(ptr2)))->inv.resources[FOOD] <= 0)
    val2 = ((*((t_player*)(ptr2)))->inv.resources[FOOD] - 1)
      * 127 + (*((t_player*)(ptr2)))->inv.cur_life;
  if (val1 > val2)
    return (1);
  if (val1 < val2)
    return (-1);
  return (0);
}

void		call_feeder()
{
  int		val;

  val = get_dmg();
  put_food(val);
  put_rock(val);
}

void			push_new_action(t_player_action pa)
{
  int			off;
  t_proc_func		ret;
  t_data_serv		ds;
  t_u_player_action	act;

  off = -1;
  ret = NULL;
  ds = get_data_serv(NULL);
  while (!(pa->player->cm.in->empty) && !ret)
    {
      if (!(ret = cmd_parse(list_front(pa->player->cm.in), &off)))
	msgout_fail(pa->player);
      else
	{
	  act.action = ret;
	  act.done = FALSE;
	  (ret == &incantation_process) ? (get_current_time(&(act.time))) :
	    (get_time_per_function(&(act.time), ret, ds->t));
	  act.player = pa->player;
	  act.param = strdup(list_front(pa->player->cm.in) + off);
	  pqueue_push(ds->action, &act, sizeof(act));
	  pa->player->cm.is_processing = TRUE;
	}
      list_pop_front(pa->player->cm.in);
    }
}
