/*
** server_routine.c for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/src/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on Wed Jun  6 21:00:33 2012 benjamin businaro
** Last update Thu Jun  7 10:01:41 2012 benjamin businaro
*/

#include <stdio.h>
#include "cmd_parse.h"
#include "string_manager.h"
#include "network.h"
#include "def.h"

void	server_routine_input(t_clientManager this)
{
  procFunc	ret;
  char		buf[BUFFER_SIZE];

  ret = NULL;
  my_receive(this->sock, buf);
  get_commands(this, buf);
  while (!this->in.empty)
    {
      printf("Processing \"%s\" ... \n", list_front(&this->in));
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
}




void	server_routine_output(t_clientManager this)
{
  while (!this->out.empty)
    {
      my_send(this->sock, list_front(&this->out))
      list_pop_front(&this->out);
    }
}
