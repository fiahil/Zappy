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

void		server_routine_input(t_data_serv ds, t_player this)
{
  procFunc	ret;
  int		off;
  char		*buf;

  ret = NULL;
  off = -1;
  (void)ds; // TODO tmp
  if ((buf = my_receive(this->cm.sock.fd)) == (char*)(-1))
    {
      this->cm.online = FALSE;
      close(this->cm.sock.fd);
      puts(".:: Client disconnected ::.");
      fflush(0);
      return ;
    }
  get_commands(this, buf);
  while (!this->cm.in->empty)
    {
      printf("Processing \"%s\" ... \n", (char*)(list_front(this->cm.in))); // TODO
      fflush(0);
      if (!(ret = cmd_parse(list_front(this->cm.in), &off)))
	{
	  puts("server_routine -> cmd_parse : Command Not Found."); // TODO
	  fflush(0);
	}
      else if (ret && !ret(this, (off != -1 ? list_front(this->cm.in) + off : NULL)))
     	{
      	  puts("server_routine : Command Failed."); // TODO
      	  fflush(0);
    	}
      list_pop_front(this->cm.in);
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
