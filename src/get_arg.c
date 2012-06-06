
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"get_arg.h"

static const	t_opt ptrtab_opt[6] =
  {
    {'c', &get_opt_c},
    {'n', &get_opt_n},
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
  args->namesOfTeams = NULL;
  args->nbPerTeam = 1;
  args->execTime = 100;
  return (0);
}

int		get_arg(int ac, char **av, t_arg *args)
{
  int		i;
  char		opt;

  init_arg(args);
  opterr = 0;
  while ((opt = getopt(ac, av, "c:n:p:t:x:y:")) != EOF)
    {
      if (opt == '?')
	{
	  usage();
	  return (-1);
	}
      else
	{
	  i = 0;
	  while (i < 6)
	    {
	      if (ptrtab_opt[i].opt == opt)
		ptrtab_opt[i].ptr_func(args);
	      ++i;
	    }
	}
    }
  return (0);
}
