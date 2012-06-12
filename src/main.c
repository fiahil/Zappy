/*
 * Fiahil
 * 06.06.2012
 */

#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "def.h"
#include "get_arg.h"
#include "network.h"
#include "netManager.h"

void		run(void)
{
  while (666)
  {
    iterClient();
  }
}

int		main(int ac, char **av)
{
  t_arg		args;

  if (get_arg(ac, av, &args) == -1)
    return (EXIT_FAILURE);
  set_connection(args.port);
  initClientTab(); // TODO camel case
  init_map(args.width, args.height);
  run();
  return (EXIT_SUCCESS);
}
