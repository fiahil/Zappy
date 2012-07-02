#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"map.h"
#include	"graphic.h"

void		msz_process(t_graphic mn, char *param, t_data_serv ds)
{
  t_map		map;

  (void)ds;
  map = get_map(NULL);
  msz(mn, map->size_x, map->size_y);
}

void		bct_process(t_graphic mn, char *param, t_data_serv ds)
{
  
}

void		mct_process(t_graphic mn, char *param, t_data_serv ds)
{
}
