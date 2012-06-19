
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

#include	"get_arg.h"

void		get_opt_c(t_arg *args)
{
  args->nb_per_team = atoi(optarg);
}

void		get_opt_p(t_arg *args)
{
  args->port = atoi(optarg);
}
