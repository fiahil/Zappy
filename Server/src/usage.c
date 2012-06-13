
#include	<stdio.h>
#include	<stdlib.h>

void		usage()
{
  fprintf(stderr, "./server ");
  fprintf(stderr, "[-p port] ");
  fprintf(stderr, "[-x width] ");
  fprintf(stderr, "[-y height] ");
  fprintf(stderr, "[-c clients_per_team] ");
  fprintf(stderr, "[-t execution_time] ");
  fprintf(stderr, "-n name_of_team_1 name_of_team_2 ...\n");
}
