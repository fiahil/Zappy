
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

#include	"get_arg.h"

void		get_opt_t(t_arg *args)
{
  args->exec_time = atoi(optarg);
}

void		get_opt_x(t_arg *args)
{
  args->width = atoi(optarg);
}

void		get_opt_y(t_arg *args)
{
  args->height = atoi(optarg);
}
