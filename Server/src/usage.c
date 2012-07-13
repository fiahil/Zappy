/*
** usage.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:13:40 2012 ulric lefevre
** Last update Thu Jul 12 19:55:24 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

void		usage()
{
  fprintf(stderr, "./zappy [-v] [-p port] [-x width] [-y height] ");
  fprintf(stderr, "[-c clients_per_team] [-t execution_time] ");
  fprintf(stderr, "-n name_of_team_1 name_of_team_2 ...\n");
}
