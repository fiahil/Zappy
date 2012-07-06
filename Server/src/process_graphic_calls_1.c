/*
** process_graphic_calls.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Tue Jun 26 11:13:01 2012 ulric lefevre
** Last update Fri Jul  6 13:06:02 2012 ulric lefevre
*/

#include	"def.h"
#include	"c_lists.h"
#include	"graphic.h"

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
