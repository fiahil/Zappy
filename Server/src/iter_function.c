/*
** iter_function.c for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/Server/src/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on Sat Jun 16 16:11:56 2012 benjamin businaro
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "handle_error.h"
#include "iter_function.h"

int	action_cleaner(void *ptr, size_t s)
{
  (void)s;
  if ((*(t_player_action*)ptr)->done == TRUE)
    return (1);
  return (0);
}

t_player	init_player()
{
  t_player player;

  if (!(player = malloc(sizeof(t_u_player))))
    handleError("malloc", strerror(errno), -1); // TODO retour erreur
  player->lvl = 1;
  player->team = "poney"; // TODO team selectionnee
  player->pos.x = 0;
  player->pos.y = 0;
  player->dir = NORTH;
  player->dead = FALSE;
  player->welcome = FALSE;
  memset(player->cm.stock, '\0', sizeof(player->cm.stock));
  player->cm.in = new_list(NULL, NULL, NULL);
  player->cm.out = new_list(NULL, NULL, NULL);
  player->cm.mode = UNKNOW;
  player->cm.is_processing = FALSE;
  player->cm.online = FALSE;
  return (player);
}

