
#include	<stdio.h>
#include	<stdlib.h>

#include	"get_arg.h"

int		parse_arg(t_arg *args)
{
  if (args->port < 0 ||
      args->width < 1 ||
      args->height < 1 ||
      args->nb_per_team < 1 ||
      args->exec_time < 1)
    return (-1);
  return (0);
}
