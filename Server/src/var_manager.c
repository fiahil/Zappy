
#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"

static t_select_manager         g_sm = 0;
static t_data_serv              g_ds = 0;

t_data_serv		get_data_serv(t_data_serv ds)
{
  if (ds != NULL)
    g_ds = ds;
  return (g_ds);
}

t_select_manager	get_select_manager(t_select_manager sm)
{
  if (sm != NULL)
    g_sm = sm;
  return (g_sm);
}
