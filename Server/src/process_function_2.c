/*
** other_process_function.c for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/src/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on Thu Jun  7 14:22:28 2012 benjamin businaro
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msgout_cmd.h"
#include "algorithm.h"
#include "team_manager.h"
#include "process_function.h"
#include "incant.h"
#include "map.h"

t_bool		broadcast_process_function(t_player this, char *data, t_data_serv info)
{
  t_iter	*it;

  (void)data;
  (void)info;
  list_push_back_new(this->cm.out, "I launch a broadcast !\n",
		     strlen("I launch a broadcast !\n") + 1);
  it = list_begin(info->player);
  while (it != list_end(info->player))
    {
      message(this, *((t_player*)it->data), data);
      it = it->next;
    }
  msgout_broadcast(this->cm.out);
  return (TRUE);
}

t_bool		incantation_process_function(t_player this, char *data, t_data_serv info)
{
  t_u_incant	incant;
  t_map		map;
  char		*log;

  (void)data;
  map = get_map(NULL);
  init_incant(&incant, this, map->map[this->pos.y][this->pos.x]);
  if (incant_is_ok(&incant))
    printf("Incant is Ok\n");
  else
    printf("Incant ain't Ok\n");
  asprintf(&log, "elevation en cours\nniveau actuel: %d\n", this->lvl);
  printf("%s\n", log);
  list_push_back_new(info->incant, &incant, sizeof(incant));
  list_push_back_new(this->cm.out, log, strlen(log) + 1);
  free(log);
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
  t_iter	*it;
  char		*str;

  (void)data;
  list_push_back_new(this->cm.out, "I ask for thr connect number !\n",
		     strlen("I ask for the connect number !\n") + 1);
  if ((it = list_find_cmp(info->teams, &func_cmp_team, this->team, 0)) == NULL)
    return (FALSE);
  asprintf(&str, "%d\n", ((t_team)it->data)->remaining);
  msgout_connect_nbr(this->cm.out, str);
  free(str);
  return (TRUE);
}
