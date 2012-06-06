/*
 * Texan
 * 06/06/2012
 */

#include <netinet/in.h>		// IPPROTO_TCP
#include <sys/socket.h>		// socket
#include <sys/types.h>		// socket
#include <string.h>		// strerror
#include <stdlib.h>		// atoi # to be removed
#include <unistd.h>
#include <errno.h>		// errno....what else ?
#include <stdio.h>		// fprintf
#include "../headers/def.h"

int	handleError(char *errFunc, char *errMsg, int fd)
{
  fprintf(stderr, "Error: %s: %s\n", errFunc, errMsg);
  if (fd > -1)
    close(fd);
  return (-1);
}

static int	setConnection(t_sockLayer server, int port)
{
  int	op;

  fprintf(stdout, "INITIALIZING CONNECTION:\n%24sInitializing socket.\n", " ");
  if ((server->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    return (handleError("socket", strerror(errno), server->fd));
  op = 1;
  fprintf(stdout, "%24sConfiguring socket.\n", " ");
  if (setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op)) < 0)
    return (handleError("setsockopt", strerror(errno), server->fd));
  fprintf(stdout, "%24sBinding socket.\n", " ");
  server->addr.sin_family = AF_INET;
  server->addr.sin_port = htons(port);
  server->addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(server->fd, (t_sockAddr)&server->addr, sizeof(server->addr)) < 0)
    return (handleError("bind", strerror(errno), server->fd));
  fprintf(stdout, "%24sSetting listening state.\n", " ");
  if (listen(server->fd, 128) < 0)
    return (handleError("listen", strerror(errno), server->fd));
  return (0);
}

int	main(int ac, char **av)
{
  // To be replaced
  t_u_sockLayer	server;

  (void)ac;
  if (setConnection(&server, atoi(av[1])) < 0)
    return (EXIT_FAILURE);
  // accept here
  return (EXIT_SUCCESS);
}
