/*
** get_arg.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:16:53 2012 ulric lefevre
** Last update Sat Jul  7 11:30:20 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

#include	"get_arg.h"

static const	t_opt g_ptrtab_opt[6] =
  {
    {'c', &get_opt_c},
    {'p', &get_opt_p},
    {'t', &get_opt_t},
    {'x', &get_opt_x},
    {'v', &get_opt_v},
    {'y', &get_opt_y}
  };

static int	init_arg(t_arg *args)
{
  args->port = 4242;
  args->width = 20;
  args->height = 20;
  args->teams = NULL;
  args->nb_per_team = 1;
  args->exec_time = 100;
  args->verbose = FALSE;
  return (0);
}

int		get_arg(int ac, char **av, t_arg *args)
{
  int		i;
  char		opt;

  init_arg(args);
  opterr = 0;
  while ((opt = getopt(ac, av, "c:n:p:t:x:vy:")) != EOF)
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
	    if (g_ptrtab_opt[i].opt == opt)
	      g_ptrtab_opt[i].ptr_func(args);
	    ++i;
	  }
      }
  get_opt_n(av, args);
  return (0);
}
