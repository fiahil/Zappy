/*
** func_ctor_dtor_1.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sun Jul  8 11:49:09 2012 ulric lefevre
** Last update Sun Jul  8 13:13:55 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"handle_error.h"

void		*ctor_team(va_list va)
{
  t_team	team;

  if ((team = malloc(sizeof(*team))) == NULL)
    crash_error("malloc", "out_of_memory");
  team->name = strdup(va_arg(va, char*));
  team->remaining = va_arg(va, int);
  return (team);
}

void		dtor_team(void *data)
{
  if (data)
    {
      if (((t_team)data)->name)
	free(((t_team)data)->name);
      free(data);
    }
}

void		dtor_player(void *data)
{
  if (data)
    {
      if ((*(t_player*)data))
	{
	  if ((*(t_player*)data)->team)
	    free((*(t_player*)data)->team);
	  delete_list((*(t_player*)data)->cm.in);
	  delete_list((*(t_player*)data)->cm.out);
	  free(*(t_player*)data);
	}
      free(data);
    }
}
