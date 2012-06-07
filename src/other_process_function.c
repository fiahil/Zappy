/*
** other_process_function.c for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/src/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on Thu Jun  7 14:22:28 2012 benjamin businaro
** Last update Thu Jun  7 20:21:30 2012 pierre martin
*/

#include <string.h>
#include "process_function.h"

t_bool	broadcast_process_function(t_clientManager this)
{

  list_push_back_new(&this->out, "I launch a broadcast !\n", strlen("I launch a broadcast !\n") + 1);

  return (TRUE);
}

t_bool	incantation_process_function(t_clientManager this)
{

  list_push_back_new(&this->out, "Incantation starting !\n", strlen("Incantation starting !\n") + 1);

  return (TRUE);
}

t_bool	fork_process_function(t_clientManager this)
{

  list_push_back_new(&this->out, "I fork !\n", strlen("I fork !\n") + 1);

  return (TRUE);
}

t_bool	connect_nbr_process_function(t_clientManager this)
{

  list_push_back_new(&this->out, "I ask for thr connect number !\n", strlen("I ask for the connect number !\n") + 1);

  return (TRUE);
}
