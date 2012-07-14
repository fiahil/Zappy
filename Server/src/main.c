/*
** main.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:37 2012 ulric lefevre
** Last update Sat Jul 14 15:31:56 2012 ulric lefevre
*/

#include	<time.h>
#include	<errno.h>
#include	<stdio.h>
#include	<signal.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"map.h"
#include	"iter.h"
#include	"clock.h"
#include	"stdout.h"
#include	"get_arg.h"
#include	"network.h"
#include	"victory.h"
#include	"func_cmp.h"
#include	"sig_manager.h"
#include	"var_manager.h"
#include	"func_cleaner.h"
#include	"handle_error.h"
#include	"func_ctor_dtor.h"
#include	"select_manager.h"

int		run(t_data_serv data_serv)
{
  t_u_select_manager	sm;

  memset(&sm, '\0', sizeof(sm));
  sm.timeout.tv_sec = 10000;
  sm.timeout.tv_usec = 10000;
  select_add(&sm, data_serv->sock.fd);
  get_data_serv(data_serv);
  get_select_manager(&sm);
  signal(SIGINT, &sig_end);
  signal(SIGTERM, &sig_end);
  while (is_there_a_victorious(data_serv))
    iter_client();
  return (0);
}

static void	init_teams(t_data_serv data_serv, t_arg *args)
{
  t_iter	*it;

  data_serv->nb_per_team = args->nb_per_team;
  it = args->teams->head;
  while (it)
    {
      list_push_front_ctor(data_serv->teams,
			   (char*)it->data, data_serv->nb_per_team);
      it = it -> next;
    }
  delete_list(args->teams);
}

static void	init_lists(t_data_serv data_serv)
{
  data_serv->monitor = new_list(NULL, NULL, NULL);
  data_serv->player = new_list(NULL, &dtor_player, NULL);
  data_serv->action = new_pqueue(&cmp_action);
  data_serv->send_q = new_list(NULL, NULL, NULL);
  data_serv->egg = new_list(NULL, &dtor_egg, NULL);
  data_serv->teams = new_list(&ctor_team, &dtor_team, NULL);
  get_data_serv(data_serv);
}

int		main(int ac, char **av)
{
  time_t	now;
  t_arg		args;
  t_u_data_serv	data_serv;

  time(&now);
  srandom(now);
  if (get_arg(ac, av, &args) == -1)
    return (EXIT_FAILURE);
  if (parse_arg(&args) == -1)
    return (EXIT_FAILURE);
  data_serv.verbose = args.verbose;
  data_serv.t = args.exec_time;
  init_map(args.width, args.height, args.teams->size);
  init_lists(&data_serv);
  init_teams(&data_serv, &args);
  stdout_logo();
  set_connection(&data_serv, args.port);
  stdout_data_serv(&args, &data_serv);
  if (run(&data_serv) < 0)
    {
      clean_all(&data_serv);
      return (EXIT_FAILURE);
    }
  clean_all(&data_serv);
  return (EXIT_SUCCESS);
}
