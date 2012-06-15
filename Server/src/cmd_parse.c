/*
 * Fiahil
 * 06.06.2012
 */

#include <stdlib.h>
#include <string.h>
#include "process_function.h"
#include "cmd_parse.h"

static const t_u_parse_elem	g_cmd_tab[] =
  {
    {6, "avance", &move_process_function},
    {6, "droite", &right_process_function},
    {6, "gauche", &left_process_function},
    {4, "voir", &look_process_function},
    {10, "inventaire", &inventory_process_function},
    {6, "prend ", &take_process_function},
    {5, "pose ", &drop_process_function},
    {7, "expulse", &expulse_process_function},
    {10, "broadcast ", &broadcast_process_function},
    {11, "incantation", &incantation_process_function},
    {4, "fork", &fork_process_function},
    {11, "connect_nbr", &connect_nbr_process_function},
    {0, NULL, NULL}
  };

static const char*		g_obj_tab[] =
  {
    "nourriture",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    NULL
  };

t_bool		match_ressource(char const *str)
{
  int		i;

  i = 0;
  while (g_obj_tab[i])
  {
    if (!strcmp(str, g_obj_tab[i]))
      return (TRUE);
    ++i;
  }
  return (FALSE);
}

procFunc	cmd_parse(char const *input, int *off)
{
  int		i;

  i = 0;
  while (g_cmd_tab[i].cmd)
  {
    if (!strncmp(input, g_cmd_tab[i].cmd, g_cmd_tab[i].size))
    {
      *off = strlen(input + g_cmd_tab[i].size);
      if ((i == 5 && !match_ressource(input + g_cmd_tab[i].size)) ||	
	  (i == 6 && !match_ressource(input + g_cmd_tab[i].size)) ||
	  (i != 8 && i != 5 && i != 6 && input[g_cmd_tab[i].size] != '\0'))
	return (NULL);
      return (g_cmd_tab[i].func);
    }
    ++i;
  }
  return (NULL);
}

