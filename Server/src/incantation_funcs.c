#include <stdio.h>
#include <string.h>
#include "def.h"

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

size_t	check_players(t_list *players, int lvl)
{
  t_iter	*it;
  size_t	count;

  count = 0;
  it = players->head;
  while ((it != NULL) && (((*(t_player*)(it->data)))->lvl == lvl))
    {
      ++count;
      it = it->next;
    }
  return (count);
}

void	level_up(t_square cell)
{
  t_iter	*it;

  it = cell->players->head;
  while (it)
    {
      ++(*(t_player *)(it->data))->lvl;
      it = it->next;
    }
}

void	fill_hashcode(t_hash hashcode, t_square cell)
{
  hashcode->nb_play = cell->players->size;
  hashcode->linemate = cell->inv.resources[LINEMATE];
  hashcode->deraumere = cell->inv.resources[DERAUMERE];
  hashcode->sibur = cell->inv.resources[SIBUR];
  hashcode->mendiane = cell->inv.resources[MENDIANE];
  hashcode->phiras = cell->inv.resources[PHIRAS];
  hashcode->thystame = cell->inv.resources[THYSTAME];
}

t_bool	incant_is_ok(t_incant incant)
{
  t_u_hash	hashcode;
  t_map		map;

  if (incant->status == FALSE)
    return (FALSE);
  map = get_map(NULL);
  if (check_players(map->map[incant->pos.y][incant->pos.x]->players , incant->incantor->lvl) != map->map[incant->pos.y][incant->pos.x]->players->size)
    {
      incant->status = FALSE;
      return (FALSE);
    }
  fill_hashcode(&hashcode, map->map[incant->pos.y][incant->pos.x]);
  if (memcmp(&incant->hashcode, &hashcode, sizeof(hashcode)))
    incant->status = FALSE;
  return (incant->status);
  /* while (++i < 7 && memcmp(&incant->hashcode, &hashcode, sizeof(hashcode))); */
  /* if (i == 7) */
  /*   { */
  /*     incant->status = FALSE; */
  /*     return (FALSE); */
  /*   } */
  /* return (TRUE); */
}

t_bool	init_incant(t_incant incant, t_player play, t_square cell)
{
  int	i;

  i = -1;
  memset(incant, 0, sizeof(*incant));
  incant->status = TRUE;
  if (check_players(cell->players, play->lvl) != cell->players->size)
    {
      printf("Players not good\n");
      incant->status = FALSE;
    }
  incant->pos.x = play->pos.x;
  incant->pos.y = play->pos.y;
  incant->incantor = play;
  //incant->timeout = ?;
  fill_hashcode(&incant->hashcode, cell);
  while (++i < 7 && memcmp(&incant->hashcode, &g_hash_cmp[i], sizeof(g_hash_cmp[i])));
  if (i == 7)
    {
      printf("Resources not good\n");
      incant->status = FALSE;
    }
  printf("Incantation set\n");
  // TEST DISPLAY
  printf("nb_play = %d\nlinemate = %d\nderaumere = %d\nsibur = %d\nmendiane = %d\nphiras = %d\nthystame = %d\nx = %d - y = %d\n",
	 incant->hashcode.nb_play,
	 incant->hashcode.linemate,
	 incant->hashcode.deraumere,
	 incant->hashcode.sibur,
	 incant->hashcode.mendiane,
	 incant->hashcode.phiras,
	 incant->hashcode.thystame,
	 incant->pos.x,
	 incant->pos.y);
  return (TRUE);
}
