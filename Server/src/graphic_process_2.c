#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"

void		tna_process(t_graphic g, char *param, t_data_serv ds)
{
}

void		ppo_process(t_graphic g, char *param, t_data_serv ds)
{
}

void		plv_process(t_graphic g, char *param, t_data_serv ds)
{
  t_iter	*it;
  int		id;

  id = atoi(param);
  it = ds->player->head;
  while (it && (((t_player)it->data)->id != id))
    it = it->next;
  plv(mn, ((t_player)it->data)->id, ((t_player)it->data)->lvl);
}
