/*
 * Fiahil
 * 06.06.2012
 */

#include <stdlib.h>
#include <string.h>
#include "cmd_parse.h"

static char const	*cmd_tab[] =
  {
    "avance",
    "droite",
    "gauche",
    "voir",
    "inventaire",
    "prend xxx",
    "pose xxx",
    "expulse",
    "broadcast xxx",
    "incantation",
    "fork",
    "connect_nbr",
    NULL
  };

t_bool		cmd_parse(char const *input)
{
  int		i;

  i = 0;
  while (cmd_tab[i])
  {
    if (!strcmp(input, cmd_tab[i]))
      return (TRUE);
    ++i;
  }
  return (FALSE);
}

