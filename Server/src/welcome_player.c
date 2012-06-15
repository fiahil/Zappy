
#include	<stdio.h>
#include	<stdlib.h>
#include	"def.h"

static int	chk_team(t_data_serv server, char *data)
{
  // chk si la team existe
  // chk s'il reste de la place dans l'equipe
  // return le nombre de client restant
}

t_boot		welcome_player(t_data_serv server, t_player player, char *data)
{
  // return false s'il faut delete le player
  // passer en accueilli le player -> et welcomed a true
  int		nb_client;

  if (data)
    {
      if ((nb_client = chk_team(server->team, data)) == -1)
	return (FALSE);
      //envoi du nombre de client restant
      list_push_back_new(player->client->out, "\n", strlen("\n") + 1);
      //envoi de la taille du monde
      list_push_back_new(player->client->out, "\n", strlen("\n") + 1);
    }
  return (TRUE);
}
