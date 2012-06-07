/*
** Made by benjamin businaro
*/

#include <stdio.h>
#include <stdlib.h>
#include "cmd_parse.h"
#include "string_manager.h"
#include "network.h"
#include "def.h"
#include "server_routine.h"

void	server_routine_input(t_clientManager this)
{
  procFunc	ret;
  char		*buf;

  ret = NULL;
  if ((buf = my_receive(this->sock->fd)) == (char*)(-1))
    {
      this->online = FALSE;
      return ;
    }
  get_commands(this, buf);
  while (!this->in.empty)
    {
      printf("Processing \"%s\" ... \n", (char*)(list_front(&this->in))); // TODO
      fflush(0);
      if (!(ret = cmd_parse(list_front(&this->in))))
	{
	  puts("server_routine -> cmd_parse : Command Not Found."); // TODO
	  fflush(0);
	}
      else if (ret && !ret())
      	{
      	  puts("server_routine : Command Failed."); // TODO
      	  fflush(0);
      	}
      list_pop_front(&this->in);
    }
  free(buf);
}




void	server_routine_output(t_clientManager this)
{
  while (!this->out.empty)
    {
      my_send(this->sock->fd, list_front(&this->out));
      list_pop_front(&this->out);
    }
}
