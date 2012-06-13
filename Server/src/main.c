/*
 * Fiahil
 * 06.06.2012
 */

#include <errno.h>

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

int		run(void)
{
  t_u_epoll_manager	epoll;

  if (init_epoll(&epoll) < 0)
    return (handleError("Aborting", "", -1));
  if (add_monitor(&epoll, get_server_fd(), NULL) < 0)
    return (handleError("Aborting", "", epoll.efd));
  epoll.ev = calloc(64, sizeof(epoll.event));
  while (666)
    iter_client(&epoll);
}

int		main(int ac, char **av)
{
  t_arg		args;

  if (get_arg(ac, av, &args) == -1)
    return (EXIT_FAILURE);
  set_connection(args.port);
  initClientTab(); // TODO camel case
  init_map(args.width, args.height);
  unitest_clock();
  if (run() < 0)
    {
      close(get_server_fd());
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
