
#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"clock.h"
#include	"incant.h"
#include	"algorithm.h"
#include	"iter_tools.h"
#include	"var_manager.h"
#include	"team_manager.h"
#include	"select_manager.h"
#include	"server_routine.h"

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
}

void		iter_action(void *ptr, size_t s)
{
  t_u_timeval	current;
  t_data_serv	ds;

  (void)s;
  get_current_time(&current);
  ds = get_data_serv(NULL);
  if (((t_player_action)ptr)->player->cm.is_processing
      && !(((t_player_action)ptr)->done)
      && cmp_time(&current, &(((t_player_action)ptr)->time)) == 1)
    {
      if (((t_player_action)ptr)->player->dead == FALSE)
	(((t_player_action)ptr)->action)
	  (((t_player_action)ptr)->player, ((t_player_action)ptr)->param, ds);
      ((t_player_action)ptr)->done = TRUE;
      ((t_player_action)ptr)->player->cm.is_processing = FALSE;
    }
	if (!((t_player_action)ptr)->player->cm.in->empty
	    && !(((t_player_action)ptr)->player->cm.is_processing))
    {
      printf("Processing \"%s\" ... \n",
	     (char*)(list_front(((t_player_action)ptr)->player->cm.in))); // TODO affichage tmp
      fflush(0);
      push_new_action((t_player_action)ptr); // TODO PARAMETRE
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
  if (cmp_time(&current, &(((t_egg)ptr)->timeout)) >= 0)
    {
      // il ne rentre pas ici ??
      printf("New player !\n");
      it = list_find_cmp(ds->teams, &func_cmp_team, ((t_egg)ptr)->fetus->team, 0);
      ((t_team)it->data)->remaining += 1;
      list_push_back_new(ds->player, &((t_egg)ptr)->fetus,
			 sizeof(((t_egg)ptr)->fetus));
      ((t_egg)ptr)->timeout.tv_sec = 0;
    }
}

void		iter_incant(void *ptr, size_t s)
{
  t_u_timeval	current;

  (void)s;
  get_current_time(&current);
  if (cmp_time(&((t_incant)ptr)->timeout, &current) <= 0)
    {
      if (incant_is_ok((t_incant)ptr))
	level_up((t_incant)ptr);
      else
	printf("Incant couldn't be performed\n");
      //msgout_incantation(((t_incant)ptr)->incantor->cm.out, ((t_incant)ptr)->incantor->lvl);
      ((t_incant)ptr)->timeout.tv_sec = 0;
    }
}
