/*
** my_itoa.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:09 2012 ulric lefevre
** Last update Sat Jun 23 20:15:10 2012 ulric lefevre
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

static char	*my_revstr(char *str)
{
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
      exit (1); // TODO retour d'erreur
  ret = memset(ret, 0, size);
  if (nb == 0)
    {
      ret[0] = '0';
      return (ret);
    }
  else
    return (my_revstr(itoa_concat(nb, ret)));
}
