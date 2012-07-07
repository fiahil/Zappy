/*
** player.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:14:47 2012 ulric lefevre
** Last update Fri Jul  6 21:32:58 2012 ulric lefevre
*/

#include	<errno.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"map.h"
#include	"player.h"
#include	"handle_error.h"

static int	g_id_player = 0;

static void	init_player(t_player player, int egg)
{
  t_map		map;

  map = get_map(NULL);
  player->id = g_id_player++;
  player->lvl = 1;
  player->team = NULL;
  player->pos.x = random() % map->size_x;
  player->pos.y = random() % map->size_y;
  player->dir = random() % 4;
  player->dead = FALSE;
  player->deleted = FALSE;
  player->welcome = FALSE;
  player->egg = egg;
  player->inv.status = FALSE;
  memset(player->inv.resources, '\0', sizeof(int) * LAST);
  player->inv.resources[FOOD] = 10;
  player->inv.cur_life = 127;
  memset(player->cm.stock, '\0', sizeof(player->cm.stock));
  player->cm.in = new_list(NULL, NULL, NULL);
  player->cm.out = new_list(NULL, NULL, NULL);
  player->cm.mode = UNKNOW;
  player->cm.is_processing = FALSE;
  player->cm.online = FALSE;
  player->cm.read = FALSE;
}

t_player	create_player(int egg)
{
  t_player	player;

  if (!(player = malloc(sizeof(t_u_player))))
    return (NULL);
  init_player(player, egg);
  if (egg == -1)
    list_push_back_new(get_map(NULL)->map[player->pos.y]
		       [player->pos.x]->players, &player, sizeof(player));
  return (player);
}

void		delete_player(t_player this)
{
  if (this)
    {
      if (this->cm.in)
	delete_list(this->cm.in);
      if (this->cm.out)
	delete_list(this->cm.out);
      if (this->team)
	free(this->team);
      free(this);
    }
}
