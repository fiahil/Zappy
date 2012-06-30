/*
** process_function_2.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:14:27 2012 ulric lefevre
** Last update Sat Jun 30 14:56:03 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"map.h"
#include	"clock.h"
#include	"incant.h"
#include	"algorithm.h"
#include	"msgout_cmd.h"
#include	"egg_manager.h"
#include	"team_manager.h"
#include	"process_function.h"
#include	"graphic.h"
#include	"iter_tools.h"
#include	"time.h"
#include	"iter_function.h"

t_bool		broadcast_process(t_player this, char *data, t_data_serv info)
{
  t_iter	*it;

  (void)data;
  (void)info;
  it = list_begin(info->player);
  while (it != list_end(info->player))
    {
      message(this, *((t_player*)it->data), data);
      it = it->next;
    }
  msgout_broadcast(this);
  pbc(info->monitor, this->id, data);
  return (TRUE);
}

t_bool		incantation_process(t_player this, char *data, t_data_serv info)
{
  t_u_player_action	act;
  t_incant		incant;
  t_map			map;

  (void)data;
  map = get_map(NULL);
  incant = malloc(sizeof(*incant));
  init_incant(incant, this, map->map[this->pos.y][this->pos.x], info->t);
  pic(info->monitor, incant, map->map[this->pos.y][this->pos.x]->players);
  if (incant->status == FALSE)
    msgout_incantation(this, -1);
  else
    {
      act.action = &iter_incant;
      get_time_per_function(&act.time, &incantation_process, info->t);
      act.player = this;
      act.param = ((char *)(incant));
      act.done = FALSE;
      pqueue_push(info->action, &(act), sizeof(act));
      msgout_incantation(this, 0);
      return (FALSE);
    }
  return (TRUE);
}

t_bool		fork_process(t_player this, char *data, t_data_serv info)
{
  t_u_egg	egg;

  (void)data;
  init_egg(&egg, this, info->t);
  list_push_back_new(info->egg, &egg, sizeof(egg));
  msgout_fork(this);
  pfk(info->monitor, this->id);
  return (TRUE);
}

t_bool		connect_nbr_process(t_player this, char *data, t_data_serv info)
{
  t_iter	*it;
  char		*str;

  (void)data;
  if ((it = list_find_cmp(info->teams, &func_cmp_team, this->team, 0)) == NULL)
    return (FALSE);
  asprintf(&str, "%d\n", ((t_team)it->data)->remaining);
  msgout_connect_nbr(this, str);
  free(str);
  return (TRUE);
}
