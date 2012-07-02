#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"graphic.h"

void		pin_process(t_graphic mn, char *param, t_data_serv ds)
{
  t_iter	*it;
  int		id;

  id = atoi(param);
  it = ds->player->head;
  while (it && (((t_player)it->data)->id != id))
    it = it->next;
  pin(mn, ((t_player)it->data));
}

void		sgt_process(t_graphic mn, char *param, t_data_serv ds)
{
  (void)param;
  sgt(mn, ds->t);
}

void		sst_process(t_graphic mn, char *param, t_data_serv ds)
{
  (void)param;
  ds->t = atoi(param);
  sgt(mn, ds->t);
}
