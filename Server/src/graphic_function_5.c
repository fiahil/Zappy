/*
 *  * Fiahil
 *   * 23/06/2012
 *    */

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graphic.h"
#include "def.h"

static t_graphic	g_mn;

static void	send_tna(void *ptr, size_t s)
{
  char		*str;

  (void)s;
  str = NULL;
  asprintf(&str, "tna %s\n", ((t_team)ptr)->name);
  mn_rep(g_mn, str);
  free(str);
}

void		msz(t_graphic mn, size_t x, size_t y)
{
  char		*str;

  str = NULL;
  asprintf(&str, "msz %lu %lu\n", x, y);
  mn_rep(mn, str);
  free(str);
}

void		tna(t_graphic mn, t_list *teams)
{
  g_mn = mn;
  list_for_each(teams, &send_tna);
}
