/*
** get_opt_2.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:16:46 2012 ulric lefevre
** Last update Sat Jul  7 11:07:10 2012 ulric lefevre
*/

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

void		get_opt_v(t_arg *args)
{
  args->verbose = TRUE;
}

void		get_opt_y(t_arg *args)
{
  args->height = atoi(optarg);
}
