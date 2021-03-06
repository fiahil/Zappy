/*
** incantation_manager.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:54 2012 ulric lefevre
** Last update Wed Jul 11 19:12:13 2012 ulric lefevre
*/

#include	<time.h>
#include	<stdio.h>
#include	<string.h>

#include	"def.h"
#include	"map.h"
#include	"clock.h"
#include	"stdout.h"
#include	"msgout_cmd.h"
#include	"res_manager.h"
#include	"process_function.h"

static t_u_hash	g_hash_cmp[] =
  {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
  };

size_t		check_players(t_list *players, int lvl)
{
  t_iter	*it;
  size_t	count;
  size_t	ref;

  count = 0;
  ref = 0;
  it = players->head;
  while (it)
    {
      if ((*(t_player*)(it->data))->cm.online)
	{
	  ++ref;
	  if ((*(t_player*)(it->data))->lvl == lvl)
	    ++count;
	}
      it = it->next;
    }
  return ((count == ref) ? ref : 0);
}

void		level_up(t_incant incant)
{
  t_iter	*it;
  t_map		map;

  map = get_map(NULL);
  it = map->map[incant->pos.y][incant->pos.x]->players->head;
  while (it)
    {
      if ((*(t_player*)(it->data))->cm.online)
	{
	  ++(*(t_player*)(it->data))->lvl;
	  stdout_player_action("Level up", (*(t_player*)(it->data))->id);
	  msgout_incantation((*(t_player*)(it->data)),
			     (*(t_player*)(it->data))->lvl);
	}
      it = it->next;
    }
  put_inv(&map->map[incant->pos.y][incant->pos.x]->inv);
}

void		fill_hashcode(t_hash hashcode, t_square cell, int nb)
{
  hashcode->nb_play = nb;
  hashcode->linemate = cell->inv.resources[LINEMATE];
  hashcode->deraumere = cell->inv.resources[DERAUMERE];
  hashcode->sibur = cell->inv.resources[SIBUR];
  hashcode->mendiane = cell->inv.resources[MENDIANE];
  hashcode->phiras = cell->inv.resources[PHIRAS];
  hashcode->thystame = cell->inv.resources[THYSTAME];
}

t_bool		incant_is_ok(t_incant incant)
{
  t_u_hash	hashcode;
  t_u_pos	pos;
  t_map		map;
  int		nb;

  if (incant->status == FALSE)
    return (FALSE);
  map = get_map(NULL);
  pos.x = incant->pos.x;
  pos.y = incant->pos.y;
  if (!(nb = check_players(map->map[pos.y][pos.x]->players,
			   incant->incantor->lvl)))
    {
      incant->status = FALSE;
      return (FALSE);
    }
  fill_hashcode(&hashcode, map->map[pos.y][pos.x], nb);
  if (memcmp(&incant->hashcode, &hashcode, sizeof(hashcode)))
    incant->status = FALSE;
  return (incant->status);
}

t_bool		init_incant(t_incant incant, t_player play, t_square cell, int t)
{
  int	nb;

  memset(incant, 0, sizeof(*incant));
  incant->status = TRUE;
  if (!(nb = check_players(cell->players, play->lvl)))
    incant->status = FALSE;
  incant->pos.x = play->pos.x;
  incant->pos.y = play->pos.y;
  incant->incantor = play;
  get_time_per_function(&incant->timeout, &incantation_process, t);
  fill_hashcode(&incant->hashcode, cell, nb);
  if (memcmp(&incant->hashcode, &g_hash_cmp[play->lvl - 1],
	     sizeof(incant->hashcode)))
    incant->status = FALSE;
  return (TRUE);
}
