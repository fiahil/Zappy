/*
** process_function.c for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/src/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on Thu Jun  7 14:12:59 2012 benjamin businaro
** Last update Thu Jun  7 14:21:17 2012 benjamin businaro
*/

#include <string.h>
#include "process_function.h"

t_bool	look_process_function(t_clientManager this)
{

  list_push_back_new(&this->out, "I look at this !\n", strlen("I look at this !\n"));

  return (TRUE);
}

t_bool	inventory_process_function(t_clientManager this)
{

  list_push_back_new(&this->out, "I check my inventory !\n", strlen("I check my inventory !\n"));

  return (TRUE);
}

t_bool	take_process_function(t_clientManager this)
{

  list_push_back_new(&this->out, "I take it !\n", strlen("I take it !\n"));

  return (TRUE);
}

t_bool	drop_process_function(t_clientManager this)
{

  list_push_back_new(&this->out, "I drop it !\n", strlen("I drop it !\n"));

  return (TRUE);
}

t_bool	expulse_process_function(t_clientManager this)
{

  list_push_back_new(&this->out, "I expulse !\n", strlen("I expulse !\n"));

  return (TRUE);
}
