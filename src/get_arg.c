
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"get_arg.h"

static const	t_opt ptrtab_opt[5] =
  {
    {'c', &get_opt_c},
    {'p', &get_opt_p},
    {'t', &get_opt_t},
    {'x', &get_opt_x},
    {'y', &get_opt_y},
  };

static int	init_arg(t_arg *args)
{
  args->port = 4242;
  args->width = 20;
  args->height = 20;
  args->names_of_teams = NULL;
  args->nb_per_team = 1;
  args->exec_time = 100;
  return (0);
}

int		get_arg(int ac, char **av, t_arg *args)
{
  int		i;
  char		opt;

  init_arg(args);
  get_opt_n(av, args);
  opterr = 0;
  while ((opt = getopt(ac, av, "c:n:p:t:x:y:")) != EOF)
    {
      if (opt != 'n' && opt == '?')
	{
	  usage();
	  return (-1);
	}
      else
	{
	  i = 0;
	  while (i < 5)
	    {
	      if (ptrtab_opt[i].opt == opt)
		ptrtab_opt[i].ptr_func(args);
	      ++i;
	    }
	}
    }
  return (0);
}
