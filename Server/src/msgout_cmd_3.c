
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
