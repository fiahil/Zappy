
#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"assert.h"
#include	"player.h"
#include	"algorithm.h"
#include	"team_manager.h"

static t_data_serv              g_ds = 0;

int		player_cleaner(void *ptr, size_t s)
{
  t_iter	*it;

  (void)s;
  if ((*(t_player*)ptr)->deleted == TRUE)
    {
      printf("Suppression du joueur %d\n", (*(t_player*)ptr)->id); // TODO affichage
      if ((*(t_player*)ptr)->team)
        {
          it = list_find_cmp(g_ds->teams, &func_cmp_team,
			     (*(t_player*)ptr)->team, 0);
          assert(it != NULL);
          ((t_team)it->data)->remaining += 1;
        }
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

int		egg_cleaner(void *ptr, size_t s)
{
  (void)s;
  if (!((t_egg)ptr)->timeout.tv_sec)
    return (1);
  return (0);
}

int		incant_cleaner(void *ptr, size_t s)
{
  (void)s;
  if (!((t_incant)ptr)->timeout.tv_sec)
    return (1);
  return (0);
}

void		set_cleaner(t_data_serv ds)
{
  g_ds = ds;
}
