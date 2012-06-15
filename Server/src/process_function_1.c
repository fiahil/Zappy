/*
** process_function.c for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/src/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on Thu Jun  7 14:12:59 2012 benjamin businaro
*/

#include <string.h>
#include "process_function.h"

t_bool		look_process_function(t_player this, char *data)
{
  (void)data;
  list_push_back_new(this->cm.out, "I look at this !\n", strlen("I look at this !\n") + 1);

  return (TRUE);
}

t_bool		inventory_process_function(t_player this, char *data)
{
  (void)data;
  list_push_back_new(this->cm.out, "I check my inventory !\n", strlen("I check my inventory !\n") + 1);
  msgout_inventaire(this->cm.out, this->inv);
  return (TRUE);
}

t_bool		take_process_function(t_player this, char *data)
{
  (void)data;
  list_push_back_new(this->cm.out, "I take it !\n", strlen("I take it !\n") + 1);

  return (TRUE);
}

t_bool		drop_process_function(t_player this, char *data)
{
  (void)data;
  list_push_back_new(this->cm.out, "I drop it !\n", strlen("I drop it !\n") + 1);

  return (TRUE);
}

t_bool		expulse_process_function(t_player this, char *data)
{
  (void)data;
  list_push_back_new(this->cm.out, "I expulse !\n", strlen("I expulse !\n") + 1);

  return (TRUE);
}
