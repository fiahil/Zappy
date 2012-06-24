/*
** func_cleaner.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:16:57 2012 ulric lefevre
** Last update Sun Jun 24 15:34:17 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"map.h"
#include	"assert.h"
#include	"player.h"
#include	"algorithm.h"
#include	"var_manager.h"
#include	"team_manager.h"

int		player_cleaner(void *ptr, size_t s)
{
  t_data_serv	ds;
  t_iter	*it;

  (void)s;
  ds = get_data_serv(NULL);
  if ((*(t_player*)ptr)->deleted == TRUE)
    {
      printf("Suppression du joueur %d\n", (*(t_player*)ptr)->id); // TODO affichage
      if ((*(t_player*)ptr)->team)
        {
          it = list_find_cmp(ds->teams, &func_cmp_team,
			     (*(t_player*)ptr)->team, 0);
          assert(it != NULL);
          ((t_team)it->data)->remaining += 1;
        }
      delete_player(*(t_player*)ptr);
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
  if (!((t_egg)ptr)->timeout.tv_sec)
    return (1);
  return (0);
}

int		incant_cleaner(void *ptr, size_t s)
{
  (void)s;
  if (!((t_incant)ptr)->timeout.tv_sec)
    return (1);
  return (0);
}

void		clean_all(t_data_serv ds)
{
  t_map	map;
  int	x;
  int	y;

  delete_list(ds->player);
  delete_list(ds->teams);
  delete_pqueue(ds->action);
  delete_list(ds->send_q);
  delete_pqueue(ds->incant);
  map = get_map(NULL);
  y = 0;
  while (y < map->size_y)
    {
      x = 0;
      while (x < map->size_x)
	delete_list(map->map[y][x++]->players);
      ++y;
    }
  free(map->map[0][0]);
  x = 0;
  while (x < map->size_y)
    free(map->map[x++]);
  free(map->map);
  free(map);
}
