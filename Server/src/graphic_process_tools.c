/*
** graphic_process_tools.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Wed Jul  4 12:15:33 2012 ulric lefevre
** Last update Mon Jul  9 19:03:57 2012 ulric lefevre
*/

#include	<unistd.h>
#include	<string.h>

#include	"def.h"

static int	g_current_id;

int		cmp_id(void *data, size_t len)
{
  t_player	player;

  (void)len;
  player = *((t_player*)data);
  if (player->id == g_current_id)
    return (1);
  return (0);
}

int		get_current_id(int id)
{
  if (id < 0)
    return (g_current_id);
  g_current_id = id;
  return (g_current_id);
}

t_bool		str_is_num(char *str)
{
  unsigned int	i;

  i = -1;
  if (!str)
    return (FALSE);
  while (str[++i] && ((str[i] >= '0') && (str[i] <= '9')));
  if (i != strlen(str))
    return (FALSE);
  return (TRUE);
}

int		epur_str(char *str, char sep)
{
  int		i;
  int		i2;
  int		nb;

  i = 0;
  i2 = -1;
  nb = 1;
  while (str[++i2] && (str[i2] == ' ' || str[i2] == '\t' || str[i2] == sep));
  while (str[i2])
    if (str[i2] && str[i2] != '\t' && str[i2] != ' ' && str[i2] != sep)
      str[i++] = str[i2++];
    else if (str[i2])
      {
	while (str[i2] && (str[i2] == ' ' || str[i2] == '\t' || str[i2] == sep))
	  i2++;
	if (str[i2] && str[i2] != '\n')
	  {
	    str[i++] = sep;
	    nb++;
	  }
      }
  str[i] = '\0';
  return (nb);
}

char		*get_params(char *str)
{
  if (!str[0] ^ !strlen(str))
    return (NULL);
  epur_str(str, ' ');
  if (!str)
    return (NULL);
  return (str);
}
