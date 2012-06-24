/*
** cmd_parse.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:17:08 2012 ulric lefevre
** Last update Sat Jun 23 20:17:09 2012 ulric lefevre
*/

#include <stdlib.h>
#include <string.h>

#include "cmd_parse.h"
#include "process_function.h"

static const t_u_parse_elem	g_cmd_tab[] =
  {
    {6, "avance", &move_process},
    {6, "droite", &right_process},
    {6, "gauche", &left_process},
    {4, "voir", &look_process},
    {10, "inventaire", &inventory_process},
    {6, "prend ", &take_process},
    {5, "pose ", &drop_process},
    {7, "expulse", &expulse_process},
    {10, "broadcast ", &broadcast_process},
    {11, "incantation", &incantation_process},
    {4, "fork", &fork_process},
    {11, "connect_nbr", &connect_nbr_process},
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

t_proc_func	cmd_parse(char const *input, int *off)
{
  int		i;

  i = 0;
  while (g_cmd_tab[i].cmd)
    {
      if (!strncmp(input, g_cmd_tab[i].cmd, g_cmd_tab[i].size))
	{
	  *off = g_cmd_tab[i].size;
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
