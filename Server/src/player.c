/*
** player.c for zappy in /home/mart_i/Work/unix/Zappy/Server/src/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Thu Jun 21 15:45:16 2012 pierre martin
** Last update Fri Jun 22 16:42:54 2012 pierre martin
*/

#include	<errno.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"map.h"
#include	"player.h"
#include	"handle_error.h"

static int	g_id_player = 0;

static void	init_player(t_player player)
{
  player->id = g_id_player++;
  player->lvl = 1;
  player->team = NULL;
  player->pos.x = random() % get_map(NULL)->size_x;
  player->pos.y = random() % get_map(NULL)->size_y;
  player->dir = random() % 4;
  player->dead = FALSE;
  player->deleted = FALSE;
  player->welcome = FALSE;
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
}

t_player	create_player()
{
  t_player player;

  if (!(player = malloc(sizeof(t_u_player))))
    handle_error("malloc", strerror(errno), -1); // TODO retour erreur
  init_player(player);
  list_push_back_new(get_map(NULL)->map[player->pos.y][player->pos.x]->players,
		     &player, sizeof(&player));
  return (player);
}

void	delete_player(t_player this)
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
