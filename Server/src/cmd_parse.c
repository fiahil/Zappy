/*
 * Fiahil
 * 06.06.2012
 */

#include <stdlib.h>
#include <string.h>
#include "process_function.h"
#include "cmd_parse.h"

t_bool	move_process_function(t_clientManager);
t_bool	right_process_function(t_clientManager);
t_bool	left_process_function(t_clientManager);

static const t_u_parse_elem	g_cmd_tab[] =
  {
    {6, "avance", &move_process_function},
    {6, "droite", &right_process_function},
    {6, "gauche", &left_process_function},
    {4, "voir", &look_process_function},
    {10, "inventaire", &inventory_process_function},
    {5, "prend xxx", &take_process_function},
    {4, "pose xxx", &drop_process_function},
    {7, "expulse", &expulse_process_function},
    {9, "broadcast xxx", &broadcast_process_function},
    {11, "incantation", &incantation_process_function},
    {4, "fork", &fork_process_function},
    {11, "connect_nbr", &connect_nbr_process_function},
    {0, NULL, NULL}
  };

/*
** TODO + buffer en param pour strtok les params
*/

t_bool	move_process_function(t_clientManager this)
{

  list_push_back_new(this->out, "I move !\n", strlen("I move !\n") + 1);

  return (TRUE);
}

t_bool	right_process_function(t_clientManager this)
{

  list_push_back_new(this->out, "I turn right !\n", strlen("I turn right !\n") + 1);

  return (TRUE);
}

t_bool	left_process_function(t_clientManager this)
{

  list_push_back_new(this->out, "I turn left !\n", strlen("I turn left !\n") + 1);

  return (TRUE);
}

procFunc	cmd_parse(char const *input)
{
  int		i;

  i = 0;
  while (g_cmd_tab[i].cmd)
  {
    if (!strncmp(input, g_cmd_tab[i].cmd, g_cmd_tab[i].size))
      return (g_cmd_tab[i].func);
    ++i;
  }
  return (NULL);
}

