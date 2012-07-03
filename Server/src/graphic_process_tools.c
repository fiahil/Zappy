#include <unistd.h>
#include <string.h>
#include "def.h"

static int	g_current_id;

t_bool	cmp_id(void *data, size_t len)
{
  t_player	player;

  (void)len;
  player = *((t_player*)data);
  if (player->id == g_current_id)
    return (0);
  return (1);
}

int	get_current_id(int id)
{
  if (id < 0)
    return (g_current_id);
  g_current_id = id;
  return (g_current_id);
}

t_bool	str_is_num(char *str)
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

