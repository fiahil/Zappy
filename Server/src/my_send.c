/*
** my_send.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:14:59 2012 ulric lefevre
** Last update Sat Jun 23 20:14:59 2012 ulric lefevre
*/

#include	<errno.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/socket.h>

#include	"handle_error.h"

int	my_send(int fd, char *msg)
{
  if (send(fd, msg, strlen(msg), MSG_NOSIGNAL) == -1)
    return (handle_error("my_send", strerror(errno), -1));
  return (0);
}
