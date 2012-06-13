
#include	<string.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	"def.h"

char*	my_receive(int fd)
{
  char	buff[BUFFER_SIZE];
  char	*ret;
  char	*tmp;
  int	test;

  test = 1;
  if ((ret = malloc(8)) == NULL)
    return (NULL);
  ret[0] = '\0';
  while (test)
    {
      if ((test = recv(fd, buff, BUFFER_SIZE - 1, 0)) == 0)
	return (ret[0] ? ret : (char*)-1);
      buff[test] = '\0';
      if ((tmp = malloc(strlen(ret) + test + 1)) == NULL)
	return (NULL);
      strcpy(tmp, ret);
      strcat(tmp, buff);
      free(ret);
      ret = tmp;
      if (test != BUFFER_SIZE - 1)
	test = 0;
    }
  return (ret);
}
