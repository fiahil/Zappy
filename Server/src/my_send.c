/*
** my_send.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:14:59 2012 ulric lefevre
** Last update Thu Jul  5 17:04:40 2012 ulric lefevre
*/

#include	<errno.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/socket.h>

#include	"handle_error.h"

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL SO_NOSIGPIPE
#endif

int		my_send(int fd, char *msg)
{
  if (send(fd, msg, strlen(msg), MSG_NOSIGNAL) == -1)
    {
      if (errno != EPIPE)
	return (handle_error("my_send", strerror(errno), -1));
      else
	{
	  errno = 0;
	  return (-2);
	}
    }
  return (0);
}
