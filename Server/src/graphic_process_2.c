#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"graphic.h"
#include	"algorithm.h"

void		tna_process(t_graphic mn, char *param, t_data_serv ds)
{
  (void)param;
  (void)ds;
  tna(mn, ds->teams);
}

void		ppo_process(t_graphic mn, char *param, t_data_serv ds)
{
  t_iter	*ret;

  if (!param[0] || !str_is_num(param))
    return ;
  get_current_id(atoi(param));
  if ((ret = list_find_if(ds->player, &cmp_id)))
    ppo(mn, *((t_player*)ret->data));
}

void		plv_process(t_graphic mn, char *param, t_data_serv ds)
{
  t_iter	*it;

  if (!param[0] || !str_is_num(param))
    return ;
  get_current_id(atoi(param));
  if ((it = list_find_if(ds->player, &cmp_id)))
    plv(mn, (*(t_player*)it->data)->id, (*(t_player*)it->data)->lvl);
}
