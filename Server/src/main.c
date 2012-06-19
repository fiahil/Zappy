/*
 * Fiahil
 * 06.06.2012
 */

#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "def.h"
#include "get_arg.h"
#include "network.h"
#include "iter.h"
#include "select_manager.h"
#include "handle_error.h"
#include "clock.h"

int		run(t_data_serv data_serv)
{
  t_u_select_manager	sm;

  memset(&sm, '\0', sizeof(t_u_select_manager));
  select_add(&sm, data_serv->sock.fd);
  while (666)
    iter_client(&sm, data_serv);
  return (0);
}

void		print_list(void *data, size_t size) // TODO affichage tmp
{
  (void)size;
  printf("name : %s\n", ((t_team)data)->name);
}

int		cmp_action(void *e1, size_t s1, void *e2, size_t s2)
{
  (void)s1;
  (void)s2;
  return (cmp_time(&((*((t_player_action*)e1))->time),
		   &((*((t_player_action*)e2))->time)));
}

static void	init_teams(t_data_serv data_serv, t_arg *args)
{
  data_serv->nb_per_team = args->nb_per_team;

  data_serv->teams = new_list(NULL, NULL, NULL);
  data_serv->teams = args->teams;
  args->teams = NULL;
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
  data_serv.player = new_list(NULL, NULL, NULL);
  init_teams(&data_serv, &args);
  data_serv.action = new_pqueue(&cmp_action);
  data_serv.send_q = new_list(NULL, NULL, NULL);
  data_serv.t = args.exec_time;
  set_connection(&data_serv, args.port);
  //  unitest_clock(); // TODO unitest
  if (run(&data_serv) < 0)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
