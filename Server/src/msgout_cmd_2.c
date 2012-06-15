
#define		_GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"msgout_cmd.h"

void		msgout_voir(t_list *out)
{
  (void)out;
  // TODO
}

void		msgout_inventaire(t_list *out, t_u_inventory inv)
{
  (void)out;
  char		*str;

  asprintf(&str, "nourriture %d,linemate %d,deraumere %d,sibur %d," \
	   "mendiane %d,phiras %d,thystame %d\n", inv.resources[FOOD],
	   inv.resources[LINEMATE], inv.resources[DERAUMERE],
	   inv.resources[SIBUR], inv.resources[MENDIANE],
	   inv.resources[PHIRAS], inv.resources[THYSTAME]);
  list_push_back_new(out, str, strlen(str));
  free(str);
}

void		msgout_prend_objet(t_list *out, t_bool is_done)
{
  (void)out;
  if (is_done)
    list_push_back_new(out, "ok\n", 4);
  else
    list_push_back_new(out, "ko\n", 4);
}

void		msgout_pose_objet(t_list *out, t_bool is_done)
{
  (void)out;
  if (is_done)
    list_push_back_new(out, "ok\n", 4);
  else
    list_push_back_new(out, "ko\n", 4);
}

void		msgout_expulse(t_list *out, t_bool is_done)
{
  (void)out;
  if (is_done)
    list_push_back_new(out, "ok\n", 4);
  else
    list_push_back_new(out, "ko\n", 4);
}
