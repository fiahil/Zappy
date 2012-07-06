/*
** process_graphic_calls_2.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Wed Jul  4 12:18:31 2012 ulric lefevre
** Last update Fri Jul  6 13:05:47 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"map.h"
#include	"graphic.h"
#include	"c_lists.h"

void		monitor_graphic(t_graphic mn, t_data_serv ds, t_player p)
{
  t_iter	*it;
  t_iter	*it2;

  msz(mn, get_map(NULL)->size_x, get_map(NULL)->size_y);
  sgt(mn, ds->t);
  bct_all(mn, get_map(NULL));
  tna(mn, ds->teams);
  it = ds->player->head;
  while (it)
    {
      pnw(ds->monitor, (*(t_player*)it->data));
      it = it->next;
    }
  it2 = ds->egg->head;
  while (it2)
    {
      enw(ds->monitor, ((t_egg)it2->data)->id, p->lvl, &p->pos);
      it2 = it2->next;
    }
}

void		player_graphic(t_list *mn, t_player this)
{
  if (this->egg >= 0)
    ebo(mn, this->egg);
  pnw(mn, this);
}

void		incend_graphic(t_data_serv ds, t_incant inc)
{
  t_iter	*it;
  t_map		map;

  pie(ds->monitor, inc);
  map = get_map(NULL);
  it = map->map[inc->pos.y][inc->pos.x]->players->head;
  while (it)
    {
      plv_general(ds->monitor,
		  (*(t_player*)(it->data))->id,
		  (*(t_player*)(it->data))->lvl);
      it = it->next;
    }
  bct_general(ds->monitor, map->map[inc->pos.y][inc->pos.x], &inc->pos);
}
