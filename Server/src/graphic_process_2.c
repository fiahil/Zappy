#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"

static int	g_current_id;

static int	cmp_id(void *p, size_t len)
{
  t_player	player;

  (void)len;
  player = *((t_player*)data);
  if (player->id == g_current_id)
    return (0);
  return (1);
}

void		tna_process(t_graphic mn, char *param, t_data_serv ds)
{
  (void)param;
  (void)ds;
  tna(mn, ds->team);
}

void		ppo_process(t_graphic mn, char *param, t_data_serv ds)
{
  t_iter	*ret;

  g_current_id = atoi(param);
  if ((ret = list_find_if(ds->player, &cmp_id)))
    ppo(mn, *((t_player*)ret->data));
}

void		plv_process(t_graphic mn, char *param, t_data_serv ds)
{
  
}
