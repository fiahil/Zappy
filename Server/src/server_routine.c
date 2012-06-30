/*
** server_routine.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:14:01 2012 ulric lefevre
** Last update Sat Jun 30 14:09:17 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<assert.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"clock.h"
#include	"stdout.h"
#include	"network.h"
#include	"algorithm.h"
#include	"cmd_parse.h"
#include	"msgout_cmd.h"
#include	"func_cleaner.h"
#include	"team_manager.h"
#include	"select_manager.h"
#include	"process_function.h"
#include	"server_routine.h"
#include	"string_manager.h"
#include	"graphic.h"

static void		init_act(t_data_serv ds, t_player this, t_proc_func ret)
{
  t_u_player_action	act;
  int			off;

  off = -1;
  while (!(this->cm.in->empty) && !ret)
    {
      if (!(ret = cmd_parse(list_front(this->cm.in), &off)))
	msgout_fail(this);
      else
	{
	  act.action = ret;
	  act.done = FALSE;
	  if (ret == &incantation_process)
	    get_current_time(&(act.time));
	  else
	    get_time_per_function(&(act.time), ret, ds->t);
	  act.player = this;
	  act.param = strdup(list_front(this->cm.in) + off);
	  pqueue_push(ds->action, &(act), sizeof(act));
	  this->cm.is_processing = TRUE;
	}
      list_pop_front(this->cm.in);
    }
}

static t_bool	welcome_new_player(t_data_serv ds, t_player this, char *buf)
{
  if (!this->welcome)
    {
      if (!welcome_player(ds, this, buf))
	{
	  this->dead = TRUE;
	  msgout_fail(this);
	}
      else
	player_graphic(ds->monitor, this);
      free(buf);
      printf("welcome_new_player\n");
      return (0);
    }
  return (1);
}

static void	process(t_player this, t_data_serv ds, t_proc_func ret)
{
  if (!(this->cm.in->empty)
      && !(this->cm.is_processing))
    {
      stdout_player_input((char*)(list_front(this->cm.in)), this->id);
      init_act(ds, this, ret);
    }
}

void		server_routine_input(t_data_serv ds, t_player this)
{
  char		*buf;
  t_proc_func	ret;
  t_iter	*it;

  ret = NULL;
  if ((buf = my_receive(this->cm.sock.fd)) == (char*)(-1))
    {
      this->cm.online = FALSE;
      if (this->team)
	{
	  it = list_find_cmp(ds->teams, &func_cmp_team, this->team, 0);
	  assert(it != NULL);
	  ((t_team)it->data)->remaining += 1;
	}
      close(this->cm.sock.fd);
      select_del(ds, this->cm.sock.fd);
      stdout_player_status("disconnected", this->id);
      return ;
    }
  get_commands(this, buf);
  if (!welcome_new_player(ds, this, buf)) // probleme ici
    {
      printf("server_routine_input\n");
      return ;
    }
  process(this, ds, ret);
  free(buf);
}

void		server_routine_output(t_data_serv ds, t_player this)
{
  (void)ds;
  assert(!this->cm.out->empty);
  my_send(this->cm.sock.fd, list_front(this->cm.out));
  list_pop_front(this->cm.out);
  if (this->dead == TRUE && this->deleted == FALSE)
  {
    this->deleted = TRUE;
    close(this->cm.sock.fd);
    select_del(ds, this->cm.sock.fd);
    this->cm.online = FALSE;
  }
}
