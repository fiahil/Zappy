/*
** Made by benjamin businaro
*/

#include <stdio.h>
#include <stdlib.h>
#include "string_manager.h"
#include "network.h"
#include "def.h"
#include "clock.h"
#include "server_routine.h"

void		server_routine_input(t_data_serv ds, t_player this)
{
  char			*buf;

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
