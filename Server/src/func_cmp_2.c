/*
** func_cmp_2.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:49:18 2012 ulric lefevre
** Last update Mon Jul  9 19:20:42 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"

int		cmp_noghost(void *data, size_t len)
{
  t_player	player;

  (void)len;
  player = *((t_player*)data);
  if (player->cm.online && !player->dead)
    return (1);
  return (0);
}
