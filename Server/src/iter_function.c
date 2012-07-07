/*
** iter_function.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:44 2012 ulric lefevre
** Last update Sat Jul  7 17:40:24 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"map.h"
#include	"clock.h"
#include	"incant.h"
#include	"stdout.h"
#include	"graphic.h"
#include	"func_cmp.h"
#include	"algorithm.h"
#include	"iter_tools.h"
#include	"msgout_cmd.h"
#include	"res_manager.h"
#include	"var_manager.h"
#include	"select_manager.h"
#include	"server_routine.h"

void			iter_rds(void *ptr, size_t s)
{
  t_player		p;
  t_select_manager	sm;
  t_data_serv		ds;

  (void)s;
  p = *(t_player*)ptr;
  sm = get_select_manager(NULL);
  ds = get_data_serv(NULL);
  if (p->cm.read && p->cm.online && p->dead == FALSE
      && select_r_isset(sm, p->cm.sock.fd))
    server_routine_input(ds, p);
  if (p->cm.online && p->deleted == FALSE && select_w_isset(sm, p->cm.sock.fd))
    server_routine_output(ds, p);
  if (!p->cm.online && p->dead == TRUE && p->deleted == FALSE)
    {
      p->deleted = TRUE;
      close(p->cm.sock.fd);
      p->cm.sock.fd = -1;
      p->cm.online = FALSE;
    }
}

void			iter_action(void *ptr, size_t s)
{
  t_u_timeval		current;
  t_data_serv		ds;
  t_bool		test;
  t_player_action	p_act;

  (void)s;
  test = FALSE;
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
  t_player	p;
  t_iter	*it;
  t_u_timeval	current;
  t_data_serv	ds;

  (void)s;
  get_current_time(&current);
  ds = get_data_serv(NULL);
  if (((t_egg)ptr)->status && cmp_time(&current,
				       &(((t_egg)ptr)->timeout)) >= 0)
    {
      p = ((t_egg)ptr)->fetus;
      stdout_serv_status("new player\n", 1);
      put_res_egg();
      it = list_find_cmp(ds->teams, &cmp_team,
			 p->team, 0);
      ((t_team)it->data)->remaining += 1;
      list_push_back_new(ds->player, &p,
			 sizeof(p));
      list_push_back_new(get_map(NULL)->map[p->pos.y]
			 [p->pos.x]->players, &p, sizeof(p));
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
  free(data);
  return (TRUE);
}

void			iter_graphic_rds(void *ptr, size_t s)
{
  t_select_manager	sm;
  t_data_serv		ds;

  (void)s;
  sm = get_select_manager(NULL);
  ds = get_data_serv(NULL);
  if (((t_graphic)ptr)->cm.online
      && select_r_isset(sm, ((t_graphic)ptr)->cm.sock.fd))
    graphic_routine_input(ds, ((t_graphic)ptr));
}
