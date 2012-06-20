
#define		_GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"map.h"
#include	"algorithm.h"
#include	"team_manager.h"

static int	chk_team(t_data_serv server, char *data)
{
  t_iter	*it;

  if ((it = list_find_cmp(server->teams, &func_cmp_team, data, 0)) == NULL)
    return (-1);
  printf("Demande de connexion a l'equipe : %s\n", ((t_team)it->data)->name);
  if (((t_team)it->data)->remaining > 0)
    ((t_team)it->data)->remaining -= 1;
  else
    return (-1);
  return (((t_team)it->data)->remaining);
}

t_bool		welcome_player(t_data_serv server, t_player player, char *data)
{
  int		nb_client;
  char		*str;
  t_map		map;

  if (data)
    {
      if ((nb_client = chk_team(server, data)) < 0)
	{
	  printf("Pas assez de place dans l'équipe ou équipe inconnue\n"); // TODO affichage tmp
	  list_push_back_new(player->cm.out, "ko\n", 4);
	  return (FALSE);
	}
      printf("test nb_client : %d\n", nb_client); // TODO affichage tmp
      asprintf(&str, "%d\n", nb_client);
      list_push_back_new(player->cm.out, str, strlen(str) + 1);
      free(str);
      map = get_map(NULL);
      asprintf(&str, "%d %d\n", map->size_x, map->size_y);
      list_push_back_new(player->cm.out, str, strlen(str) + 1);
      free(str);
      player->welcome = TRUE;
      player->team = strdup(data);
      list_pop_front(player->cm.in);
    }
  return (TRUE);
}
