/*
** welcome_player.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:12:58 2012 ulric lefevre
** Last update Sun Jul  8 23:15:12 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"map.h"
#include	"stdout.h"
#include	"graphic.h"
#include	"func_cmp.h"
#include	"algorithm.h"

static int	chk_team(t_data_serv server, char *data)
{
  char		*str;
  t_iter	*it;

  if (!strcmp(data, "GRAPHIC"))
    return (-2);
  if ((it = list_find_cmp(server->teams, &cmp_team, data, 0)) == NULL)
    return (-1);
  str = NULL;
  asprintf(&str, "Demande de connexion a l'equipe : %s\n",
	   ((t_team)it->data)->name);
  stdout_serv_status(str, 0);
  free(str);
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

static void	init_ghost(t_iter **ghost, t_player *p, int nb_c)
{
  t_map		map;
  char		*str;

  delete_list((*(t_player*)(*ghost)->data)->cm.in);
  delete_list((*(t_player*)(*ghost)->data)->cm.out);
  memcpy(&((*(t_player*)(*ghost)->data)->cm), &((*p)->cm), sizeof((*p)->cm));
  (*(t_player*)(*ghost)->data)->welcome = TRUE;
  map = get_map(NULL);
  asprintf(&str, "%d\n%d %d\n", nb_c, map->size_x, map->size_y);
  list_push_back_new((*(t_player*)(*ghost)->data)->cm.out,
		     str, strlen(str) + 1);
  list_pop_front((*(t_player*)(*ghost)->data)->cm.in);
  free(str);
  (*p)->dead = TRUE;
  (*p)->deleted = TRUE;
  (*p)->cm.online = FALSE;
  (*p)->cm.sock.fd = -1;
  (*p)->cm.out = NULL;
  (*p)->cm.in = NULL;
}

static void	first_contact(t_player *p, int nb_c, char *data)
{
  t_map		map;
  char		*str;

  str = NULL;
  map = get_map(NULL);
  asprintf(&str, "%d\n%d %d\n", nb_c, map->size_x, map->size_y);
  list_push_back_new((*p)->cm.out, str, strlen(str) + 1);
  free(str);
  (*p)->welcome = TRUE;
  (*p)->team = strdup(data);
  list_pop_front((*p)->cm.in);
}

t_bool		welcome_player(t_data_serv server, t_player player)
{
  int		nb_client;
  t_iter	*ghost;
  char		*data;

  data = list_front(player->cm.in);
  if (data)
    {
      if ((nb_client = chk_team(server, data)) < 0)
	{
	  (nb_client == -2) ? (welcome_graphic(server, player)) :
	    (stdout_serv_status("Equipe complete ou equipe inconnue\n", 0));
	  return (FALSE);
	}
      if ((ghost = list_find_cmp(server->player, &team_ghost, data, 0)))
	{
	  init_ghost(&ghost, &player, nb_client);
	  player_graphic(server->monitor, (*(t_player*)ghost->data));
	  return (TRUE);
	}
      first_contact(&player, nb_client, data);
    }
  player_graphic(server->monitor, player);
  return (TRUE);
}
