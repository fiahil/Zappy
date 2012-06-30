/*
** func_cleaner.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:16:57 2012 ulric lefevre
** Last update Fri Jun 29 20:38:20 2012 ulric lefevre
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

int		player_cleaner(void *ptr, size_t s)
{
  char		*str;
  t_data_serv	ds;
  t_iter	*it;

  (void)s;
  str = NULL;
  ds = get_data_serv(NULL);
  if ((*(t_player*)ptr)->deleted == TRUE)
    {
      asprintf(&str, "Suppression du joueur %d\n", (*(t_player*)ptr)->id);
      stdout_serv_status(str, 0);
      free(str);
      g_current = (*(t_player*)ptr);
      list_remove_if(&(get_data_serv(NULL)->action->queue), &del_player_action);
      if ((*(t_player*)ptr)->team)
        {
          it = list_find_cmp(ds->teams, &func_cmp_team,
			     (*(t_player*)ptr)->team, 0);
          assert(it != NULL);
          ((t_team)it->data)->remaining += 1;
        }
      map_cleaner(*(t_player*)ptr);
      delete_player(*(t_player*)ptr);
      g_current = NULL;
      return (1);
    }
  return (0);
}

int		action_cleaner(void *ptr, size_t s)
{
  (void)s;
  if (((t_player_action)ptr)->done == TRUE)
    {
      free(((t_player_action)ptr)->param);
      return (1);
    }
  return (0);
}

int		egg_cleaner(void *ptr, size_t s)
{
  (void)s;
  if (!((t_egg)ptr)->status)
    return (1);
  return (0);
}
