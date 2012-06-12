/*
 * Fiahil
 * 12.06.2012
 */

#include <stdlib.h>
#include "def.h"

static t_list	*g_action_list = 0;
static t_list	*g_send_list = 0;

t_list		*get_action_list()
{
  if (g_action_list == NULL)
    g_action_list = new_list(NULL, NULL, NULL);
  return (g_action_list);
}

t_list		*get_send_list()
{
  if (g_send_list == NULL)
    g_send_list = new_list(NULL, NULL, NULL);
  return (g_send_list);
}

void		flush_send_list()
{
  void		*data;

  while (!g_send_list->empty)
  {
    data = list_front(g_send_list);
    list_pop_front(g_send_list);
    server_routine_output((t_clientManager)data);
  }
}
