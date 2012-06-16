
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"

static int	func_cmp(char *s1, size_t s1len, char *s2, size_t s2len)
{
  (void)s1len;
  (void)s2len;
  return (strcmp(s1, s2));
}

static int	chk_team(t_data_serv server, char *data)
{
  // chk s'il reste de la place dans l'equipe
  // return le nombre de client restant
  if (!list_find_cmp(server->team, &func_cmp, data, 0))
    return (-1);
  return (0);
}

t_bool		welcome_player(t_data_serv server, t_player player, char *data)
{
  // return false s'il faut delete le player
  // passer en accueilli le player -> et welcomed a true
  int		nb_client;

  if (data)
    {
      if ((nb_client = chk_team(server->team, data)) == -1)
	return (FALSE);
      //envoi du nombre de client restant
      list_push_back_new(player->cm.out, "\n", strlen("\n") + 1);
      //envoi de la taille du monde
      list_push_back_new(player->cm.out, "\n", strlen("\n") + 1);
    }
  return (TRUE);
}
