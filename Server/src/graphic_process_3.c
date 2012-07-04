#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"graphic.h"

static t_bool	str_is_num(char *str)
{
  unsigned int	i;

  i = -1;
  if (!str)
    return (FALSE);
  while (str[++i] && ((str[i] >= '0') && (str[i] <= '9')));
  if (i != strlen(str))
    return (FALSE);
  return (TRUE);
}

void		pin_process(t_graphic mn, char *param, t_data_serv ds)
{
  t_iter	*it;
  int		id;

  if (!param || !str_is_num(param))
    return ;
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
  if (!param)
    return ;
  if (!str_is_num(param))
    return ;
  ds->t = atoi(param);
  if (!ds->t)
    ds->t = 1;
  sgt(mn, ds->t);
}
