
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

void		msgout_avance(t_list *out)
{
  list_push_back_new(out, "ok", 3);
}

void		msgout_droite(t_list *out)
{
  list_push_back_new(out, "ok", 3);
}

void		msgout_gauche(t_list *out)
{
  list_push_back_new(out, "ok", 3);
}

void		msgout_voir(t_list *out)
{
  
}

void		msgout_inventaire(t_list *out)
{
  
}

void		msgout_prend_objet(t_list *out, t_bool is_done)
{
  if (is_done)
    list_push_back_new(out, "ok", 3);
  else
    list_push_back_new(out, "ko", 3);
}

void		msgout_pose_objet(t_list *out, t_bool is_done)
{
  if (is_done)
    list_push_back_new(out, "ok", 3);
  else
    list_push_back_new(out, "ko", 3);
}

void		msgout_expulse(t_list *out, t_bool is_done)
{
  if (is_done)
    list_push_back_new(out, "ok", 3);
  else
    list_push_back_new(out, "ko", 3);
}

void		msgout_broadcast(t_list *out)
{
  list_push_back_new(out, "ok", 3);
}

void		msgout_incantation(t_list *out)
{
  
}

void		msgout_fork(t_list *out)
{
  list_push_back_new(out, "ok", 3);
}

void		msgout_connect_nbr(t_list *out)
{
  
}

void		msgout_mort(t_list *out)
{
  list_push_back_new(out, "mort", 5);
}
