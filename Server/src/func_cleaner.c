
#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"player.h"

int		player_cleaner(void *ptr, size_t s)
{
  (void)s;
  if ((*(t_player*)ptr)->deleted == TRUE)
    {
      printf("Suppression du joueur %d\n", (*(t_player*)ptr)->id); // TODO affichage 
      delete_player(*(t_player*)ptr);
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
