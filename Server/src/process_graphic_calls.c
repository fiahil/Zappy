#include "graphic.h"
#include "c_lists.h"
#include "def.h"

void	drop_graphic(t_list *monitor, t_player this, t_square pos, int res)
{
  pdr(monitor, this->id, res);
  pin_general(monitor, this);
  bct_general(monitor, pos, &this->pos);
}

void	take_graphic(t_list *monitor, t_player this, t_square pos, int res)
{
  pgt(monitor, this->id, res);
  pin_general(monitor, this);
  bct_general(monitor, pos, &this->pos);
}

void	expulse_graphic(t_list *monitor, t_player this, t_list *play)
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
