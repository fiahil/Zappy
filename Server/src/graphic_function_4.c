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

void		edi(t_list *mn, int id)
{
  char		*str;

  str = NULL;
  asprintf(&str, "edi #%d\n", id);
  mn_push(mn, str);
  free(str);
}

void            ebo(t_list *mn, int id)
{
  char          *str;

  str = NULL;
  asprintf(&str, "ebo #%d\n", id);
  mn_push(mn, str);
  free(str);
}

void            eht(t_list *mn, int id)
{
  char          *str;

  str = NULL;
  asprintf(&str, "eht #%d\n", id);
  mn_push(mn, str);
  free(str);
}

void		enw(t_list *mn, int egg, int player, t_pos p)
{
  char		*str;

  str = NULL;
  asprintf(&str, "enw #%d #%d %d %d\n", egg, player, p->x, p->y);
  mn_push(mn, str);
  free(str);
}
