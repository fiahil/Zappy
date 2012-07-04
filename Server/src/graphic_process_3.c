/*
** graphic_process_3.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Wed Jul  4 12:14:54 2012 ulric lefevre
** Last update Wed Jul  4 12:14:55 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"graphic.h"
#include	"algorithm.h"
#include	"graphic_tools.h"

void		pin_process(t_graphic mn, char *param, t_data_serv ds)
{
  t_iter	*it;

  if (!param[0] || !str_is_num(param))
    return ;
  get_current_id(atoi(param));
  if ((it = list_find_if(ds->player, &cmp_id)))
    pin(mn, (*(t_player*)it->data));
}

void		sgt_process(t_graphic mn, char *param, t_data_serv ds)
{
  (void)param;
  sgt(mn, ds->t);
}

void		sst_process(t_graphic mn, char *param, t_data_serv ds)
{
  if (!param[0])
    return ;
  if (!str_is_num(param))
    return ;
  ds->t = atoi(param);
  if (!ds->t)
    ds->t = 1;
  sgt(mn, ds->t);
}
