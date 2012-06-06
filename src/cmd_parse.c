/*
 * Fiahil
 * 06.06.2012
 */

#include <stdlib.h>
#include <string.h>
#include "cmd_parse.h"

static const t_u_parse_elem	g_cmd_tab[] =
  {
    {"avance", NULL},
    {"droite", NULL},
    {"gauche", NULL},
    {"voir", NULL},
    {"inventaire", NULL},
    {"prend xxx", NULL},
    {"pose xxx", NULL},
    {"expulse", NULL},
    {"broadcast xxx", NULL},
    {"incantation", NULL},
    {"fork", NULL},
    {"connect_nbr", NULL},
    {NULL, NULL}
  };

procFunc	cmd_parse(char const *input)
{
  int		i;

  i = 0;
  while (g_cmd_tab[i].cmd)
  {
    if (!strcmp(input, g_cmd_tab[i].cmd))
      return (g_cmd_tab[i].func);
    ++i;
  }
  return (NULL);
}

