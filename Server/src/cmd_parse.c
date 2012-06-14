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
    {5, "prend xxx", &take_process_function},
    {4, "pose xxx", &drop_process_function},
    {7, "expulse", &expulse_process_function},
    {9, "broadcast xxx", &broadcast_process_function},
    {11, "incantation", &incantation_process_function},
    {4, "fork", &fork_process_function},
    {11, "connect_nbr", &connect_nbr_process_function},
    {0, NULL, NULL}
  };

procFunc	cmd_parse(char const *input, int *off)
{
  int		i;

  i = 0;
  while (g_cmd_tab[i].cmd)
  {
    if (!strncmp(input, g_cmd_tab[i].cmd, g_cmd_tab[i].size))
    {
      *off = strlen(input + g_cmd_tab[i].size);
      return (g_cmd_tab[i].func);
    } 
    ++i;
  }
  return (NULL);
}

