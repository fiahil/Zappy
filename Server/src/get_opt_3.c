
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"get_arg.h"
#include	"def.h"

static void	get_default_names(t_arg *args)
{
  list_push_front_ctor(args->teams, "Poney", args->nb_per_team);
}

static void	*ctor_team(va_list va)
{
  t_team	team;

  if ((team = malloc(sizeof(*team))) == NULL)
    return (NULL);
  team->name = strdup(va_arg(va, char*));
  team->remaining = va_arg(va, int);
  return (team);
}

static void	dtor_team(void *data)
{
  if (data)
    {
      if (((t_team)data)->name)
	free(((t_team)data)->name);
      free(data);
    }
}

void		get_opt_n(char **av, t_arg *args)
{
  int		found;

  args->teams = new_list(&ctor_team, &dtor_team, NULL);
  found = 0;
  while (!found && av && (*av))
    {
      if (strcmp((*av), "-n") == 0)
	found = 1;
      ++av;
    }
  if (found)
    while (found && av && (*av))
      {
	if (strncmp((*av), "-", 1) == 0)
	  found = 0;
	if (found)
	  list_push_front_ctor(args->teams, *av, args->nb_per_team);
	++av;
      }
  else
    get_default_names(args);
}
