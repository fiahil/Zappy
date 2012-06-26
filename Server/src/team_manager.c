/*
** team_manager.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:13:44 2012 ulric lefevre
** Last update Sat Jun 23 20:13:45 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"

int		func_cmp_team(void *s1, size_t s1len, void *s2, size_t s2len)
{
  (void)s1len;
  (void)s2len;
  return (strcmp(((t_team)s1)->name, (char*)s2));
}
