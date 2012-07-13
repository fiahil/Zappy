/*
** get_opt_3.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:16:42 2012 ulric lefevre
** Last update Fri Jul 13 16:33:10 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"get_arg.h"
#include	"handle_error.h"
#include	"func_ctor_dtor.h"

static void	get_default_names(t_arg *args)
{
  list_push_front_new(args->teams, "Koala", 6);
  list_push_front_new(args->teams, "Poney", 6);
}

void		get_opt_n(char **av, t_arg *args)
{
  int		found;

  if ((args->teams = new_list(NULL, NULL, NULL)) == NULL)
    crash_error("malloc", "out_of_memory");
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
	  list_push_front_new(args->teams, *av, strlen(*av) + 1);
	++av;
      }
  else
    get_default_names(args);
}
