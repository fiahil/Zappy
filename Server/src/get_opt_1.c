/*
** get_opt_1.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:16:49 2012 ulric lefevre
** Last update Sat Jun 23 20:16:50 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

#include	"get_arg.h"

void		get_opt_c(t_arg *args)
{
  args->nb_per_team = atoi(optarg);
}

void		get_opt_p(t_arg *args)
{
  args->port = atoi(optarg);
}
