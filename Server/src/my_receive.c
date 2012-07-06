/*
** my_receive.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:15:02 2012 ulric lefevre
** Last update Mon Jul  2 11:23:54 2012 ulric lefevre
*/

#include	<stdlib.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/socket.h>

#include	"def.h"

static void	*cleaner(char * buf, void *ret)
{
  if (buf != ret)
    free(buf);
  return (ret);
}

char*		my_receive(int fd)
{
  char		buff[BUFFER_SIZE];
  char		*ret;
  char		*tmp;
  int		test;

  test = 1;
  if ((ret = malloc(8)) == NULL)
    return (NULL);
  memset(ret, '\0', 8);
  while (test)
    {
      if ((test = recv(fd, buff, BUFFER_SIZE - 1, 0)) <= 0)
	return (cleaner(ret, ret[0] ? ret : (char*)-1));
      buff[test] = '\0';
      if ((tmp = malloc(strlen(ret) + test + 1)) == NULL)
	return (cleaner(ret, NULL));
      memset(tmp, '\0', strlen(ret) + test + 1);
      strcpy(tmp, ret);
      strcat(tmp, buff);
      free(ret);
      ret = tmp;
      if (test != BUFFER_SIZE - 1)
	test = 0;
    }
  return (ret);
}
