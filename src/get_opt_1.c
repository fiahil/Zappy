
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"get_arg.h"

void		get_opt_c(t_arg *args)
{
  args->nbPerTeam = atoi(optarg);
}

void		get_opt_n(t_arg *args)
{
  (void)args; // faire une liste chainée
  return ;
}

void		get_opt_p(t_arg *args)
{
  args->port = atoi(optarg);
}
