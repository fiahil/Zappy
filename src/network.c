/*
** network.c for zappy in /home/mart_i/Work/unix/Zappy/src/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Wed Jun  6 20:41:43 2012 pierre martin
*/

#include	<netinet/in.h>		// IPPROTO_TCP
#include	<sys/socket.h>		// socket
#include	<sys/types.h>		// socket
#include	<string.h>		// strerror
#include	<stdlib.h>		// atoi # to be removed
#include	<unistd.h>
#include	<errno.h>		// errno....what else ?
#include	<netdb.h>
#include	<stdio.h>		// fprintf

#include	"handle_error.h"
#include	"def.h"

static t_sockLayer	g_server;

int	set_connection(int port)
{
  int	op;

  if ((g_server = malloc(sizeof(*g_server))) == NULL)
    return (handleError("malloc", strerror(errno), -1));
  fprintf(stdout, "INITIALIZING CONNECTION:\n%24sInitializing socket.\n", " ");
  if ((g_server->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    return (handleError("socket", strerror(errno), g_server->fd));
  op = 1;
  fprintf(stdout, "%24sConfiguring socket.\n", " ");
  if (setsockopt(g_server->fd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op)) < 0)
    return (handleError("setsockopt", strerror(errno), g_server->fd));
  fprintf(stdout, "%24sBinding socket.\n", " ");
  g_server->addr.sin_family = AF_INET;
  g_server->addr.sin_port = htons(port);
  g_server->addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(g_server->fd, (t_sockAddr)&(g_server->addr), sizeof(t_u_sockAddrIn)) < 0)
    return (handleError("bind", strerror(errno), g_server->fd));
  fprintf(stdout, "%24sSetting listening state.\n", " ");
  if (listen(g_server->fd, 128) < 0)
    return (handleError("listen", strerror(errno), g_server->fd));
  return (0);
}

int	accept_connection(t_sockLayer sock)
{
  socklen_t	len;

  len = sizeof((sock->addr));
  if ((sock->fd = accept(g_server->fd, (t_sockAddr)&(sock->addr), &len)) == -1)
    return (handleError("accept", strerror(errno), sock->fd));
  return (0);
}

// recv: tant que retour != 0
int	my_receive(t_sockLayer sock, char *buff)
{
  if (recv(sock->fd, buff, BUFFER_SIZE - 1, 0) < 0)
    return (handleError("recv", strerror(errno), -1));
  return (0);
}
// send: tant que toujours des datas

int	my_send(t_sockLayer sock, char* msg)
{
  if (send(sock->fd, msg, strlen(msg), 0))
    return (handleError("send", strerror(errno), -1));
  return (0);
}
