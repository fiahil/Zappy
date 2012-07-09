/*
** server_routine.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:14:01 2012 ulric lefevre
** Last update Mon Jul  9 14:56:48 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"clock.h"
#include	"stdout.h"
#include	"graphic.h"
#include	"network.h"
#include	"func_cmp.h"
#include	"algorithm.h"
#include	"cmd_parse.h"
#include	"msgout_cmd.h"
#include	"func_cleaner.h"
#include	"select_manager.h"
#include	"server_routine.h"
#include	"string_manager.h"
#include	"process_function.h"

static void		init_act(t_data_serv ds, t_player this)
{
  t_u_player_action	act;
  t_proc_func		ret;
  int			off;

  off = -1;
  ret = NULL;
  while (!(this->cm.in->empty) && !ret)
    {
      if (!(ret = cmd_parse(list_front(this->cm.in), &off)))
	msgout_fail(this);
      else
	{
	  act.action = ret;
	  act.done = FALSE;
	  (ret == &incantation_process) ? (get_current_time(&(act.time))) :
	    (get_time_per_function(&(act.time), ret, ds->t));
	  act.player = this;
	  act.param = strdup(list_front(this->cm.in) + off);
	  pqueue_push(ds->action, &(act), sizeof(act));
	  if (!strcmp(list_front(this->cm.in), "fork"))
	    pfk(ds->monitor, this->id);
	  this->cm.is_processing = TRUE;
	}
      list_pop_front(this->cm.in);
    }
}

static t_bool	welcome_new_player(t_data_serv ds, t_player this)
{
  if (!this->welcome && list_front(this->cm.in))
    {
      if (!welcome_player(ds, this))
	{
	  this->dead = TRUE;
	  msgout_fail(this);
	}
      return (0);
    }
  return (1);
}

static void	process(t_player this, t_data_serv ds)
{
  if (!(this->cm.in->empty)
      && !(this->cm.is_processing))
    {
      stdout_player_input((char*)(list_front(this->cm.in)), this->id);
      init_act(ds, this);
    }
}

void		server_routine_input(t_data_serv ds, t_player this)
{
  char		*buf;
  t_iter	*it;

  if ((buf = my_receive(this->cm.sock.fd)) == (char*)(-1))
    {
      this->cm.online = FALSE;
      if (this->team)
	{
	  it = list_find_cmp(ds->teams, &cmp_team, this->team, 0);
	  ((t_team)it->data)->remaining += 1;
	}
      get_current(this);
      list_remove_if(&(ds->action->queue), &del_player_action);
      close(this->cm.sock.fd);
      this->cm.sock.fd = -1;
      select_del(ds, this->cm.sock.fd);
      stdout_player_status("deconnexion", this->id);
      return ;
    }
  get_commands(this, buf);
  free(buf);
  this->cm.read = FALSE;
  if (!welcome_new_player(ds, this))
    return ;
  process(this, ds);
}

void		server_routine_output(t_data_serv ds, t_player this)
{
  (void)ds;
  if (my_send(this->cm.sock.fd, list_front(this->cm.out)) == -2)
    {
      this->dead = TRUE;
      get_current(this);
      list_remove_if(&(ds->action->queue), &del_player_action);
      stdout_player_status("deconnexion", this->id);
    }
  list_pop_front(this->cm.out);
  if (this->dead == TRUE && this->deleted == FALSE)
  {
    this->deleted = TRUE;
    close(this->cm.sock.fd);
    this->cm.sock.fd = -1;
    select_del(ds, this->cm.sock.fd);
    if (this->team && this->cm.online)
      ++(((t_team)(list_find_cmp(ds->teams,
				 &cmp_team, this->team, 0))->data)->remaining);
    this->cm.online = FALSE;
  }
}
