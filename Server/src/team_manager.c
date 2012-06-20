
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"

int		func_cmp_team(void *s1, size_t s1len, void *s2, size_t s2len)
{
  (void)s1len;
  (void)s2len;
  return (strcmp(((t_team)s1)->name, (char*)s2));
}
