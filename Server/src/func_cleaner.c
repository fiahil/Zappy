
#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"

int		player_cleaner(void *ptr, size_t s)
{
  (void)s;
  if (((t_player)ptr)->dead == TRUE)
    {
      printf("Suppression du joueur %d\n", ((t_player)ptr)->id); // TODO affichage tmp
      free(((t_player)ptr)->team);
      return (1);
    }
  return (0);
}

int		action_cleaner(void *ptr, size_t s)
{
  (void)s;
  if (((t_player_action)ptr)->done == TRUE)
    {
      free(((t_player_action)ptr)->param);
      return (1);
    }
  return (0);
}
