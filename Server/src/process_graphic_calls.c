/*
** process_graphic_calls.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Tue Jun 26 11:13:01 2012 ulric lefevre
** Last update Tue Jun 26 11:13:15 2012 ulric lefevre
*/

#include "graphic.h"
#include "c_lists.h"
#include "map.h"
#include "def.h"

void		drop_graphic(t_list *monitor, t_player this, t_square pos, int res)
{
  pdr(monitor, this->id, res);
  pin_general(monitor, this);
  bct_general(monitor, pos, &this->pos);
}

void		take_graphic(t_list *monitor, t_player this, t_square pos, int res)
{
  pgt(monitor, this->id, res);
  pin_general(monitor, this);
  bct_general(monitor, pos, &this->pos);
}

void		expulse_graphic(t_list *monitor, t_player this, t_list *play)
{
  t_iter	*it;

  pex(monitor, this->id);
  it = play->head;
  while (it)
    {
      if ((*(t_player*)(it->data))->id != this->id)
	ppo_general(monitor, (*(t_player*)(it->data)));
      it = it->next;
    }
}

void		monitor_graphic(t_graphic mn, t_data_serv ds, t_player p)
{
  msz(mn, get_map(NULL)->size_x, get_map(NULL)->size_y);
  sgt(mn, ds->t);
  bct_all(mn, get_map(NULL));
  tna(mn, ds->teams);
  pnw(ds->monitor, p);
  enw(ds->monitor, ds->egg->size, p->lvl, &p->pos);
}
