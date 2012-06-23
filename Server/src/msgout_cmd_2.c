/*
** msgout_cmd_2.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:18 2012 ulric lefevre
** Last update Sat Jun 23 20:15:18 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"msgout_cmd.h"

void		msgout_voir(t_list *out, char *look)
{
  list_push_back_new(out, look, strlen(look) + 1);
}

void		msgout_inventaire(t_list *out, t_u_inventory inv)
{
  char		*str;

  str = NULL;
  asprintf(&str, "{nourriture %d,linemate %d,deraumere %d,sibur %d," \
	   "mendiane %d,phiras %d,thystame %d}\n", inv.resources[FOOD],
	   inv.resources[LINEMATE], inv.resources[DERAUMERE],
	   inv.resources[SIBUR], inv.resources[MENDIANE],
	   inv.resources[PHIRAS], inv.resources[THYSTAME]);
  list_push_back_new(out, str, strlen(str) + 1);
  free(str);
}

void		msgout_prend_objet(t_list *out, t_bool is_done)
{
  if (is_done)
    list_push_back_new(out, "ok\n", 4);
  else
    list_push_back_new(out, "ko\n", 4);
}

void		msgout_pose_objet(t_list *out, t_bool is_done)
{
  if (is_done)
    list_push_back_new(out, "ok\n", 4);
  else
    list_push_back_new(out, "ko\n", 4);
}

void		msgout_expulse(t_list *out, t_bool is_done)
{
  if (is_done)
    list_push_back_new(out, "ok\n", 4);
  else
    list_push_back_new(out, "ko\n", 4);
}
