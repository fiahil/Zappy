/*
** Made by benjamin businaro
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "def.h"
#include "clock.h"
#include "network.h"
#include "cmd_parse.h"
#include "msgout_cmd.h"
#include "server_routine.h"
#include "string_manager.h"

static void		init_act(t_data_serv ds, t_player this, t_proc_func ret)
{
  t_player_action	act;
  int			off;

  off = -1;
  while (!(this->cm.in->empty) && !ret)
    {
      if (!(ret = cmd_parse(list_front(this->cm.in), &off)))
	msgout_fail(this->cm.out);
      else
	{
	  if (!(act = malloc(sizeof(*act))))
	    exit(1); // TODO
	  act->action = ret;
	  act->done = FALSE;
	  get_time_per_function(&(act->time), ret, ds->t);
	  act->player = this;
	  act->param = strdup(list_front(this->cm.in) + off);
	  pqueue_push(ds->action, &(act), sizeof(&act));
	  this->cm.is_processing = TRUE;
	}
      list_pop_front(this->cm.in);
    }
}

void		server_routine_input(t_data_serv ds, t_player this)
{
  char			*buf;
  t_proc_func		ret;

  ret = NULL;
  if ((buf = my_receive(this->cm.sock.fd)) == (char*)(-1))
    {
      this->cm.online = FALSE;
      close(this->cm.sock.fd);
      puts(".:: Client disconnected ::.");
      fflush(0);
      return ;
    }
  get_commands(this, buf);
  /* if (!this->welcome && !welcome_player(ds, this, buf)) */
  /*   { */
  /*     this->dead = TRUE; */
  /*     free(buf); */
  /*     return ; */
  /*   } */
  if (!(this->cm.in->empty)
      && !(this->cm.is_processing))
    {
      printf("Processing \"%s\" ... \n",
	     (char*)(list_front(this->cm.in))); // TODO
      init_act(ds, this, ret);
      fflush(0);
    }
  free(buf);
}

void		server_routine_output(t_data_serv ds, t_player this)
{
  (void)ds; // TODO tmp
  while (!this->cm.out->empty)
    {
      my_send(this->cm.sock.fd, list_front(this->cm.out));
      list_pop_front(this->cm.out);
    }
}
