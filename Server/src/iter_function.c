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
#include "map.h"
#include "clock.h"

int	action_cleaner(void *ptr, size_t s)
{
  (void)s;
  if ((*(t_player_action*)ptr)->done == TRUE)
    {
      free((*(t_player_action*)ptr)->param);
      return (1);
    }
  return (0);
}

t_player	init_player()
{
  t_player player;

  if (!(player = malloc(sizeof(t_u_player))))
    handleError("malloc", strerror(errno), -1); // TODO retour erreur
  player->lvl = 1;
  player->team = "poney"; // TODO team selectionnee
  player->pos.x = random() % get_map(NULL)->size_x;
  player->pos.y = random() % get_map(NULL)->size_y;
  player->dir = random() % 4;
  player->dead = FALSE;
  player->welcome = FALSE;
  player->inv.status = FALSE;
  memset(player->inv.resources, '\0', sizeof(int) * LAST);
  player->inv.resources[FOOD] = 10;
  memset(player->cm.stock, '\0', sizeof(player->cm.stock));
  player->cm.in = new_list(NULL, NULL, NULL);
  player->cm.out = new_list(NULL, NULL, NULL);
  player->cm.mode = UNKNOW;
  player->cm.is_processing = FALSE;
  player->cm.online = FALSE;
  list_push_back_new(get_map(NULL)->map[player->pos.y][player->pos.x]->players,
		     &player, sizeof(&player));
  return (player);
}

void	set_timeout_select(t_player_action *ptr, t_timeval time)
{
  t_u_timeval	current;

  if (!ptr)
    {
      time->tv_usec = 100;
      time->tv_sec = 100;
      return ;
    }
  get_current_time(&current);
  if ((*ptr)->time.tv_usec - current.tv_usec < 0)
    time->tv_usec = 0;
  else
    time->tv_usec = (*ptr)->time.tv_usec - current.tv_usec;
  if ((*ptr)->time.tv_sec - current.tv_sec < 0)
    time->tv_sec = 0;
  else
    time->tv_sec = (*ptr)->time.tv_sec - current.tv_sec;
}
