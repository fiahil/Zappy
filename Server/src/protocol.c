
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"def.h"

void		protocol_avance(t_list *out)
{
  list_push_back_new(out, "ok", 3);
}

void		protocol_droite(t_list *out)
{
  list_push_back_new(out, "ok", 3);
}

void		protocol_gauche(t_list *out)
{
  list_push_back_new(out, "ok", 3);
}

void		protocol_voir(t_list *out)
{
  (void)out;
}

void		protocol_inventaire(t_list *out)
{
  (void)out;
}

void		protocol_prend_objet(t_list *out, t_bool is_done)
{
  if (is_done)
    list_push_back_new(out, "ok", 3);
  else
    list_push_back_new(out, "ko", 3);
}

void		protocol_pose_objet(t_list *out, t_bool is_done)
{
  if (is_done)
    list_push_back_new(out, "ok", 3);
  else
    list_push_back_new(out, "ko", 3);
}

void		protocol_expulse(t_list *out, t_bool is_done)
{
  if (is_done)
    list_push_back_new(out, "ok", 3);
  else
    list_push_back_new(out, "ko", 3);
}

void		protocol_broadcast(t_list *out)
{
  list_push_back_new(out, "ok", 3);
}

void		protocol_incantation(t_list *out)
{
  (void)out;
}

void		protocol_fork(t_list *out)
{
  list_push_back_new(out, "ok", 3);
}

void		protocol_connect_nbr(t_list *out)
{
  (void)out;
}

void		protocol_mort(t_list *out)
{
  list_push_back_new(out, "mort", 5);
}
