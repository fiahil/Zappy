/*
** iter_function.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:44 2012 ulric lefevre
** Last update Sun Jul  1 15:30:18 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"clock.h"
#include	"incant.h"
#include	"stdout.h"
#include	"algorithm.h"
#include	"iter_tools.h"
#include	"var_manager.h"
#include	"team_manager.h"
#include	"select_manager.h"
#include	"server_routine.h"
#include	"msgout_cmd.h"
#include	"graphic.h"

void		iter_rds(void *ptr, size_t s)
{
  t_select_manager	sm;
  t_data_serv		ds;

  (void)s;
  sm = get_select_manager(NULL);
  ds = get_data_serv(NULL);
  if ((*(t_player*)ptr)->cm.online && (*(t_player*)ptr)->dead == FALSE
      && select_r_isset(sm, (*(t_player*)ptr)->cm.sock.fd))
    server_routine_input(ds, *(t_player*)ptr);
  if ((*(t_player*)ptr)->cm.online && (*(t_player*)ptr)->deleted == FALSE
      && select_w_isset(sm, (*(t_player*)ptr)->cm.sock.fd))
    server_routine_output(ds, *(t_player*)ptr);
  if (!(*(t_player*)ptr)->cm.online && (*(t_player*)ptr)->dead == TRUE &&
      (*(t_player*)ptr)->deleted == FALSE)
  {
    (*(t_player*)ptr)->deleted = TRUE;
    close((*(t_player*)ptr)->cm.sock.fd);
    (*(t_player*)ptr)->cm.online = FALSE;
  }
}

void		iter_action(void *ptr, size_t s)
{
  t_u_timeval	current;
  t_data_serv	ds;
  t_bool	test;
  t_player_action p_act;

  (void)s;
  p_act = (t_player_action)ptr;
  get_current_time(&current);
  ds = get_data_serv(NULL);
  if (p_act->player->cm.is_processing && !(p_act->done)
      && cmp_time(&current, &(p_act->time)) == 1)
    {
      if (p_act->player->dead == FALSE)
	test = (p_act->action)(p_act->player, p_act->param, ds);
      p_act->done = TRUE;
      if (test)
	p_act->player->cm.is_processing = FALSE;
    }
  if (!p_act->player->cm.in->empty && !(p_act->player->cm.is_processing))
    {
      stdout_player_input((char*)(list_front(p_act->player->cm.in)),
			  p_act->player->id);
      push_new_action(p_act);
    }
}

void		iter_egg(void *ptr, size_t s)
{
  t_iter	*it;
  t_u_timeval	current;
  t_data_serv	ds;

  (void)s;
  get_current_time(&current);
  ds = get_data_serv(NULL);
  if (((t_egg)ptr)->status && cmp_time(&current,
				       &(((t_egg)ptr)->timeout)) >= 0)
    {
      stdout_serv_status("new player\n", 0);
      it = list_find_cmp(ds->teams, &func_cmp_team,
			 ((t_egg)ptr)->fetus->team, 0);
      ((t_team)it->data)->remaining += 1;
      list_push_back_new(ds->player, &((t_egg)ptr)->fetus,
			 sizeof(((t_egg)ptr)->fetus));
      ((t_egg)ptr)->status = FALSE;
      eht(ds->monitor, ((t_egg)ptr)->id);
    }
}

t_bool		iter_incant(t_player this, char *data, t_data_serv info)
{
  (void)info;
  (void)this;
  if (incant_is_ok((t_incant)data))
    level_up((t_incant)data);
  else
    msgout_incantation(this, -1);
  ((t_incant)data)->incantor->cm.is_processing = FALSE;
  incend_graphic(info, ((t_incant)data));
  return (TRUE);
}
