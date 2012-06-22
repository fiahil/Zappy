
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
  printf("Connection query to : %s\n", ((t_team)it->data)->name);
  if (((t_team)it->data)->remaining > 0)
    ((t_team)it->data)->remaining -= 1;
  else
    return (-1);
  return (((t_team)it->data)->remaining);
}

static int	team_ghost(void *this, size_t len, void *cmp, size_t l2)
{
  (void)len;
  (void)l2;
  if (cmp && (*(t_player*)this)->team &&
      !strcmp((*(t_player*)this)->team, (char*)cmp) &&
      !(*(t_player*)this)->cm.online)
    return (0);
  return (-1);
}

t_bool		welcome_player(t_data_serv server, t_player player, char *data)
{
  int		nb_client;
  char		*str;
  t_map		map;
  t_iter	*ghost;

  if (data)
    {
      if ((nb_client = chk_team(server, data)) < 0)
	{
	  printf("Not enough slot in the team or team unknown\n"); // TODO affichage tmp
	  list_push_back_new(player->cm.out, "ko\n", 4);
	  return (FALSE);
	}
      if ((ghost = list_find_cmp(server->player, &team_ghost, data, 0)))
	{
	  (*(t_player*)ghost->data)->cm.in = player->cm.in;

	  (*(t_player*)ghost->data)->cm.out = player->cm.out;

	  memcpy(&((*(t_player*)ghost->data)->cm), &player->cm, sizeof(player->cm));
	  (*(t_player*)ghost->data)->welcome = TRUE;
	  map = get_map(NULL);
	  asprintf(&str, "%d\n%d %d\n", nb_client, map->size_x, map->size_y);
	  list_push_back_new((*(t_player*)ghost->data)->cm.out, str, strlen(str) + 1);
	  free(str);
	  player->dead = TRUE;
	  player->deleted = TRUE;
	  player->cm.online = FALSE;
	  player->cm.out = NULL;
	  player->cm.in = NULL;
	  return(TRUE);
	}
      printf("test nb_client : %d\n", nb_client); // TODO affichage tmp
      map = get_map(NULL);
      asprintf(&str, "%d\n%d %d\n", nb_client, map->size_x, map->size_y);
      list_push_back_new(player->cm.out, str, strlen(str) + 1);
      free(str);
      player->welcome = TRUE;
      player->team = strdup(data);
      list_pop_front(player->cm.in);
    }
  return (TRUE);
}
