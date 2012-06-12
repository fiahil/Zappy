
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	"get_arg.h"

static void	get_default_names(t_arg *args)
{
  list_push_front_new(args->names_of_teams, "Au poney fringant of the death", 31);
}

void		get_opt_c(t_arg *args)
{
  args->nb_per_team = atoi(optarg);
}

void		get_opt_n(char **av, t_arg *args)
{
  int		found;

  args->names_of_teams = new_list(NULL, NULL, NULL);
  found = 0;
  while (!found && av && *av)
    {
      if (strcmp(*av, "-n") == 0)
	found = 1;
      ++av;
    }
  if (found)
    while (found && av && *av)
      {
	if (strncmp(*av, "-", 1) == 0)
	  found = 0;
	if (found)
	  list_push_front_new(args->names_of_teams, *av, strlen(*av) + 1);
	++av;
      }
  else
    get_default_names(args);
}

void		get_opt_p(t_arg *args)
{
  args->port = atoi(optarg);
}
