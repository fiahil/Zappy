/*
** Made by benjamin businaro
*/

#include <stdio.h>
#include "cmd_parse.h"
#include "string_manager.h"
#include "server_routine.h"

void	server_routine_input(t_clientManager this)
{
  procFunc	ret;
  char		*buf;

  ret = NULL;
  // TODO RECV -> buf
  buf = NULL; // TODO
  get_commands(this, buf);
  while (!this->in.empty)
    {
      if (!(ret = cmd_parse(list_front(&this->in))))
	{
	  puts("server_routine -> cmd_parse : Command Not Found."); // TODO
	  fflush(0);
	}
      else
	ret(); // TODO push direct dans l'ouput et return un booleen (gestion des erreur)
      list_pop_front(&this->in);
    }
}




void	server_routine_output(t_clientManager this)
{
  while (!this->out.empty)
    {
      // TODO SEND (list_front(&this->out))
      list_pop_front(&this->out);
    }
}
