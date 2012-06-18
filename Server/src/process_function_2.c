/*
** other_process_function.c for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/src/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on Thu Jun  7 14:22:28 2012 benjamin businaro
*/

#include <string.h>

#include "msgout_cmd.h"
#include "process_function.h"

t_bool		broadcast_process_function(t_player this, char *data, t_data_serv info)
{
  t_iter	*it;

  (void)data;
  (void)info;
  list_push_back_new(this->cm.out, "I launch a broadcast !\n",
		     strlen("I launch a broadcast !\n") + 1);
  it = list_begin(info->player);
  printf("list.size = %ld\n", info->player->size);
  while (it != list_end(info->player))
    {
      message(this, *((t_player*)it->data), data);
      printf("Sending %s...\n", data);
      it = it->next;
    }
  msgout_broadcast(this->cm.out);
  return (TRUE);
}

t_bool		incantation_process_function(t_player this, char *data, t_data_serv info)
{
  (void)data;
  (void)info;
  list_push_back_new(this->cm.out, "Incantation starting !\n",
		     strlen("Incantation starting !\n") + 1);

  return (TRUE);
}

t_bool		fork_process_function(t_player this, char *data, t_data_serv info)
{
  (void)data;
  (void)info;
  list_push_back_new(this->cm.out, "I fork !\n", strlen("I fork !\n") + 1);
  msgout_fork(this->cm.out);
  return (TRUE);
}

t_bool		connect_nbr_process_function(t_player this, char *data, t_data_serv info)
{
  (void)data;
  (void)info;
  list_push_back_new(this->cm.out, "I ask for thr connect number !\n",
		     strlen("I ask for the connect number !\n") + 1);

  return (TRUE);
}
