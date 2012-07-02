/*
** func_cleaner.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:16:57 2012 ulric lefevre
** Last update Mon Jul  2 14:45:08 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"map.h"
#include	"stdout.h"
#include	"assert.h"
#include	"player.h"
#include	"algorithm.h"
#include	"res_manager.h"
#include	"var_manager.h"
#include	"team_manager.h"
#include	"process_function.h"

static t_player	g_current = NULL;

int		del_player_action(void *ptr, size_t s)
{
  (void)s;
  if (g_current && ((t_player_action)ptr)->player == g_current)
    return (1);
  return (0);
}

void		map_cleaner(t_player p)
{
  t_iter	*tmp;

  tmp = list_find_cmp(get_map(NULL)->map[p->pos.y][p->pos.x]->players,
      &cmp_player_list, p, sizeof(*p));
  list_extract(get_map(NULL)->map[p->pos.y][p->pos.x]->players, tmp);
  delete_iter(tmp, NULL);
}

t_player	get_current(t_player p)
{
  if (p != NULL)
    g_current = p;
  return (g_current);
}

int		player_cleaner(void *ptr, size_t s)
{
  char		*str;
  t_data_serv	ds;
  t_player	p;

  (void)s;
  p = *(t_player*)ptr;
  str = NULL;
  ds = get_data_serv(NULL);
  if (p->deleted == TRUE)
    {
      asprintf(&str, "Suppression du joueur %d\n", p->id);
      stdout_serv_status(str, 0);
      free(str);
      g_current = p;
      list_remove_if(&(ds->action->queue), &del_player_action);
      if (p->team)
	++(((t_team)(list_find_cmp(ds->teams, &func_cmp_team,
				   p->team, 0))->data)->remaining);
      map_cleaner(p);
      delete_player(p);
      g_current = NULL;
      return (1);
    }
  return (0);
}
