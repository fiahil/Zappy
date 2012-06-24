/*
** main.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:37 2012 ulric lefevre
** Last update Sat Jun 23 20:55:52 2012 ulric lefevre
*/

#include	<time.h>
#include	<errno.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"map.h"
#include	"iter.h"
#include	"clock.h"
#include	"get_arg.h"
#include	"network.h"
#include	"func_cmp.h"
#include	"var_manager.h"
#include	"func_cleaner.h"
#include	"handle_error.h"
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
  while (666)
    iter_client();
  return (0);
}

void		print_list(void *data, size_t size) // TODO affichage tmp
{
  (void)size;
  printf("name : %s -> size : %d\n",
	 ((t_team)data)->name, ((t_team)data)->remaining);
}

static void	init_teams(t_data_serv data_serv, t_arg *args)
{
  data_serv->nb_per_team = args->nb_per_team;
  data_serv->teams = args->teams;
  args->teams = NULL;
}

static void	init_lists(t_data_serv data_serv)
{
  data_serv->monitor = new_list(NULL, NULL, NULL);
  data_serv->player = new_list(NULL, NULL, NULL);
  data_serv->action = new_pqueue(&cmp_action);
  data_serv->send_q = new_list(NULL, NULL, NULL);
  data_serv->incant = new_pqueue(&cmp_incant);
  data_serv->egg = new_list(NULL, NULL, NULL);
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
  printf("port : %d\n", args.port); // TODO affichage tmp
  printf("width : %d\n", args.width); // TODO affichage tmp
  printf("height : %d\n", args.height); // TODO affichage tmp
  list_for_each(args.teams, &print_list); // TODO affichage tmp
  printf("nb clients per team : %d\n", args.nb_per_team); // TODO affichage tmp
  printf("execution time : %d\n", args.exec_time); // TODO affichage tmp
  init_map(args.width,
	   args.height,
	   (args.teams->size * args.nb_per_team));
  init_teams(&data_serv, &args);
  init_lists(&data_serv);
  data_serv.t = args.exec_time;
  set_connection(&data_serv, args.port);
  if (run(&data_serv) < 0)
    {
      clean_all(&data_serv);
      return (EXIT_FAILURE);
    }
  clean_all(&data_serv);
  return (EXIT_SUCCESS);
}
