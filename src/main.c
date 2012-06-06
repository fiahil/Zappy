/*
 * Fiahil
 * 06.06.2012
 */

#include <string.h>
#include <stdlib.h>
#include "def.h"
#include "get_arg.h"
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
  /* setConnections(/\* port ? *\/); */
  initClientTab();
  run();
  return (EXIT_SUCCESS);
}
