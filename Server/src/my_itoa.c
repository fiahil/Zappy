/*
** my_itoa.c for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/Server/src
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on  Thu Jun 14 20:25:39 2012 benjamin businaro
*/

#include <stdlib.h>
#include <string.h>
#include "my_itoa.h"

static const char	*g_intTab[] =
  {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

static size_t	itoa_size(size_t nb, size_t ret)
{
  if (nb <= 0)
    return (ret);
  return (itoa_size(nb / 10, ret + 1));
}

static char	*itoa_concat(size_t nb, char *ret)
{
  if (nb <= 0)
    return (ret);
  return (itoa_concat(nb / 10, strcat(ret, g_intTab[nb % 10])));
}

static char	*my_revstr(char *str) {
  int	size;
  int	it;
  char	swap;

  it = 0;
  size = strlen(str) - 1;
  while (it < size)
    {
      swap = str[it];
      str[it] = str[size];
      str[size] = swap;
      ++it;
      --size;
    }
  return (str);
}

char	*my_itoa(size_t nb)
{
  char		*ret;
  size_t	size;

  if (nb == 0)
    size = 2;
  else
    size = itoa_size(nb, 0) + 1;
  if (!(ret = malloc(sizeof(*ret) * size)))
      exit (1); // TODO
  ret = memset(ret, 0, size);
  if (nb == 0)
    {
      ret[0] = '0';
      return (ret);
    }
  else
    return (my_revstr(itoa_concat(nb, ret)));
}
