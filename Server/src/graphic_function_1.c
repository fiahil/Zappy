/*
 * Fiahil
 * 23/06/2012
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graphic.h"
#include "def.h"

void		sbp(t_list *mn)
{
  mn_push(mn, "sbp\n");
}

void		suc(t_list *mn)
{
  mn_push(mn, "suc\n");
}

void		smg(t_list *mn, char const *msg)
{
  char		*str;

  str = NULL;
  asprintf(&str, "smg %s\n", msg);
  mn_push(mn, str);
  free(str);
}
