#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"map.h"
#include	"graphic.h"

void		msz_process(t_graphic mn, char *param, t_data_serv ds)
{
  t_map		map;

  (void)param;
  (void)ds;
  map = get_map(NULL);
  msz(mn, map->size_x, map->size_y);
}

void		bct_process(t_graphic mn, char *param, t_data_serv ds)
{
  (void)param;
  (void)ds;
  // pas fait
}

void		mct_process(t_graphic mn, char *param, t_data_serv ds)
{
  (void)param;
  (void)ds;
  bct_all(mn, get_map(NULL));
}
