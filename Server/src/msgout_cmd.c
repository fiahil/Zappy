
#define		_GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"msgout_cmd.h"

void		msgout_avance(t_list *out)
{
  list_push_back_new(out, "ok\n", 4);
}

void		msgout_droite(t_list *out)
{
  list_push_back_new(out, "ok\n", 4);
}

void		msgout_gauche(t_list *out)
{
  list_push_back_new(out, "ok\n", 4);
}

void		msgout_voir(t_list *out)
{
  // TODO
}

void		msgout_inventaire(t_list *out, t_u_inventory inv)
{
  char		*str;

  asprintf(&str, "nourriture %d,linemate %d,deraumere %d,sibur %d," \
	   "mendiane %d,phiras %d,thystame %d\n", inv.resources[FOOD],
	   inv.resources[LINEMATE], inv.resources[DERAUMERE],
	   inv.resources[SIBUR], inv.resources[MENDIANE],
	   inv.resources[PHIRAS], inv.resources[THYSTAME])
  list_push_back_new(out, str, strlen(str));
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

void		msgout_broadcast(t_list *out)
{
  list_push_back_new(out, "ok\n", 4);
}

void		msgout_incantation(t_list *out)
{
  // TODO
}

void		msgout_fork(t_list *out)
{
  list_push_back_new(out, "ok\n", 4);
}

void		msgout_connect_nbr(t_list *out)
{
  // TODO
}

void		msgout_mort(t_list *out)
{
  list_push_back_new(out, "mort\n", 6);
}
