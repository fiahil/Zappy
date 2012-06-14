/*
 * Fiahil
 * 06.06.2012
 */

#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "def.h"
#include "get_arg.h"
#include "network.h"
#include "netManager.h"
#include "epoll_manager.h"
#include "handle_error.h"
#include "clock.h"

int		run(t_data_serv data_serv)
{
  t_u_epoll_manager	epoll;

  if (init_epoll(&epoll) < 0)
    return (handleError("Aborting", "", -1));
  if (add_monitor(&epoll, data_serv->sock.fd, NULL) < 0)
    return (handleError("Aborting", "", epoll.efd));
  epoll.ev = calloc(64, sizeof(epoll.event));
  while (666)
    iter_client(&epoll, data_serv);
  return (0);
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
  data_serv.player = new_list(NULL, NULL, NULL);
  data_serv.action = new_list(NULL, NULL, NULL);
  data_serv.send_q = new_list(NULL, NULL, NULL);
  set_connection(&data_serv, args.port);
  init_map(args.width, args.height, (args.names_of_teams->size * args.nb_per_team));
  unitest_clock(); // TODO unitest
  if (run(&data_serv) < 0)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
