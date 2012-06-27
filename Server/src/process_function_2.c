/*
** process_function_2.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:14:27 2012 ulric lefevre
** Last update Mon Jun 25 15:31:25 2012 ulric lefevre
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

///////
t_bool		do_incant(t_player this, char *data, t_data_serv info)
{
  //t_u_timeval	current;

  (void)info;
  (void)this;
  //get_current_time(&current);
  printf("BITE\n");
  /* if (cmp_time(&((t_incant)data)->timeout, &current) <= 0) */
  /*   { */
  printf("DATA = %p | %d\n", data, ((t_incant)data)->status);
  if (incant_is_ok((t_incant)data))
    level_up((t_incant)data);
  else
    printf("Incant couldn't be performed\n");
  ((t_incant)data)->incantor->cm.is_processing = FALSE;
  //((t_incant)data)->timeout.tv_sec = 0;
      //}
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
  if (incant->status == FALSE)
    {
      printf("Incant ain't Ok\n");
      get_current_time(&incant->timeout);
    }
  else
    {
      printf("Incant is Ok\n");
      //this->cm.is_processing = TRUE;
      act.action = &do_incant;
      get_time_per_function(&act.time, &incantation_process, info->t);
      printf("time = %s\n", ctime(&act.time.tv_sec));
      act.player = this;
      printf("CAST = %p\n", incant);
      act.param = ((char *)(incant));
      act.done = FALSE;
      //push_new_action(&act);
      pqueue_push(info->action, &(act), sizeof(act));
      //pqueue_push(info->incant, &incant, sizeof(incant));
      msgout_incantation(this, this->lvl);
      return (FALSE);
    }
  return (TRUE);
}

t_bool		fork_process(t_player this, char *data, t_data_serv info)
{
  t_u_egg	egg;

  (void)data;
  init_egg(&egg, this, info->t);
  list_push_front_new(info->egg, &egg, sizeof(egg));
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
