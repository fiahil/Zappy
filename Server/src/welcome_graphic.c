/*
** welcome_graphic.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Tue Jun 26 11:26:32 2012 ulric lefevre
** Last update Tue Jun 26 11:32:18 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"graphic.h"

void		welcome_graphic(t_data_serv ds, t_player p)
{
  t_u_graphic	mn;

  puts("Monitor connection");
  memcpy(&mn.cm, &p->cm, sizeof(mn));
  memset(&mn.cm.stock, '\0', sizeof(mn.cm.stock));
  mn.cm.in = new_list(NULL, NULL, NULL);
  mn.cm.out = new_list(NULL, NULL, NULL);
  mn.cm.mode = UNKNOW;
  list_push_back_new(ds->monitor, &mn, sizeof(mn));
  p->cm.sock.fd = -1;
  p->cm.online = FALSE;
  monitor_graphic(&mn, ds, p);
}
