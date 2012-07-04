#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"map.h"
#include	"graphic.h"
#include	"graphic_tools.h"

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
  t_u_pos	pos;
  t_map		map;
  char		*tmp;

  (void)ds;
  if (!param[0])
    return ;
  if (!str_is_num(tmp = strtok(param, " " )))
    return ;
  pos.x = atoi(tmp);
  if (!str_is_num(tmp = strtok(NULL, " ")))
    return ;
  pos.y = atoi(tmp);
  if (strtok(NULL, " "))
    return ;
  map = get_map(NULL);
  if ((pos.x > map->size_x - 1) || (pos.y > map->size_y - 1))
    return ;
  bct(mn, map->map[pos.y][pos.x], &pos);
}

void		mct_process(t_graphic mn, char *param, t_data_serv ds)
{
  (void)param;
  (void)ds;
  bct_all(mn, get_map(NULL));
}
