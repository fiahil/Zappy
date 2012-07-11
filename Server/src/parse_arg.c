/*
** parse_arg.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:14:40 2012 ulric lefevre
** Last update Wed Jul 11 18:52:44 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"get_arg.h"

int		parse_arg(t_arg *args)
{
  if (args->port < 1 ||
      args->width < 2 ||
      args->height < 2 ||
      args->nb_per_team < 1 ||
      args->exec_time < 1)
    return (-1);
  return (0);
}
