
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"msgout_cmd.h"

void		msgout_broadcast(t_list *out)
{
  list_push_back_new(out, "ok\n", 4);
}

void		msgout_incantation(t_list *out)
{
  (void)out;
  // TODO
}

void		msgout_fork(t_list *out)
{
  list_push_back_new(out, "ok\n", 4);
}

void		msgout_connect_nbr(t_list *out)
{
  (void)out;
  // TODO
}

void		msgout_mort(t_list *out)
{
  list_push_back_new(out, "mort\n", 6);
}
