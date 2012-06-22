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


  memset(&sm, '\0', sizeof(sm));
  sm.timeout.tv_sec = 10000;
  sm.timeout.tv_usec = 10000;
  select_add(&sm, data_serv->sock.fd);
  while (666)
    iter_client(&sm, data_serv);
  return (0);
}

void		print_list(void *data, size_t size) // TODO affichage tmp
{
  (void)size;
  printf("name : %s -> size : %d\n", ((t_team)data)->name, ((t_team)data)->remaining);
}

int		cmp_incant(void *e1, size_t s1, void *e2, size_t s2)
{
  (void)s1;
  (void)s2;
  return (cmp_time(&((*((t_incant*)e1))->timeout),
		   &((*((t_incant*)e2))->timeout)));
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
  data_serv->teams = args->teams;
  args->teams = NULL;
}

void		clean_all(t_data_serv ds)
{
  t_map	map;
  int	x;
  int	y;

  delete_list(ds->player);
  delete_list(ds->teams);
  delete_pqueue(ds->action);
  delete_list(ds->send_q);
  delete_pqueue(ds->incant);
  map = get_map(NULL);
  y = 0;
  while (y < map->size_y)
    {
      x = 0;
      while (x < map->size_x)
	delete_list(map->map[y][x++]->players);
      ++y;
    }
  free(map->map[0][0]);
  x = 0;
  while (x < map->size_y)
    free(map->map[x++]);
  free(map->map);
  free(map);
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
  data_serv.player = new_list(NULL, NULL, NULL);
  data_serv.action = new_pqueue(&cmp_action);
  data_serv.send_q = new_list(NULL, NULL, NULL);
  data_serv.incant = new_pqueue(&cmp_incant);
  data_serv.egg = new_list(NULL, NULL, NULL);
  data_serv.t = args.exec_time;
  set_connection(&data_serv, args.port);
  //  unitest_clock(); // TODO unitest
  if (run(&data_serv) < 0)
    {
      clean_all(&data_serv);
      return (EXIT_FAILURE);
    }
  clean_all(&data_serv);
  return (EXIT_SUCCESS);
}
