
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"algorithm.h"

static int	func_cmp(void *s1, size_t s1len, void *s2, size_t s2len)
{
  (void)s1len;
  (void)s2len;
  return (strcmp(((t_team)s1)->name, (char*)s2));
}

static int	chk_team(t_data_serv server, char *data)
{
  // chk s'il reste de la place dans l'equipe
  // return le nombre de client restant
  t_iter	*it;

  if ((it = list_find_cmp(server->teams, &func_cmp, data, 0)) == NULL)
    return (-1);
  printf("Demande de connexion a l'equipe : %s\n", ((t_team)it->data)->name);
  ((t_team)it->data)->remaining -= 1;
  return (((t_team)it->data)->remaining);
}

t_bool		welcome_player(t_data_serv server, t_player player, char *data)
{
  // return false s'il faut delete le player
  // passer en accueilli le player -> et welcomed a true
  int		nb_client;

  if (data)
    {
      if ((nb_client = chk_team(server, data)) == -1)
	return (FALSE);
      printf("test nb_client : %d\n", nb_client); // TODO affichage tmp
      //envoi du nombre de client restant
      list_push_back_new(player->cm.out, "\n", strlen("\n") + 1);
      //envoi de la taille du monde
      list_push_back_new(player->cm.out, "\n", strlen("\n") + 1);
    }
  return (TRUE);
}
