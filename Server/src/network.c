/*
** network.c for zappy in /home/mart_i/Work/unix/Zappy/src/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Wed Jun  6 20:41:43 2012 pierre martin
*/

#include	<netinet/in.h>
#include	<sys/socket.h>
#include	<sys/types.h>
#include	<string.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<errno.h>
#include	<netdb.h>
#include	<stdio.h>

#include	"epoll_manager.h"
#include	"network.h"
#include	"handle_error.h"
#include	"def.h"

int	set_connection(t_data_serv data_serv, int port)
{
  int	op;

  fprintf(stdout, "INITIALIZING CONNECTION:\n%24sInitializing socket.\n", " ");
  if ((data_serv->sock.fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    return (handleError("socket", strerror(errno), data_serv->sock.fd));
  op = 1;
  fprintf(stdout, "%24sConfiguring socket.\n", " ");
  if (setsockopt(data_serv->sock.fd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op)) < 0)
    return (handleError("setsockopt", strerror(errno), data_serv->sock.fd));
  fprintf(stdout, "%24sBinding socket.\n", " ");
  data_serv->sock.addr.sin_family = AF_INET;
  data_serv->sock.addr.sin_port = htons(port);
  data_serv->sock.addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(data_serv->sock.fd, (t_sockAddr)&(data_serv->sock.addr), sizeof(t_u_sockAddrIn)) < 0)
    return (handleError("bind", strerror(errno), data_serv->sock.fd));
  fprintf(stdout, "%24sSetting listening state.\n", " ");
  if (listen(data_serv->sock.fd, 128) < 0)
    return (handleError("listen", strerror(errno), data_serv->sock.fd));
  return (0);
}

int	accept_connection(t_epoll_manager epoll, t_data_serv data_serv, t_player p)
{
  socklen_t	len;

  len = sizeof(p->cm.sock.addr);
  if ((p->cm.sock.fd = accept(data_serv->sock.fd, (t_sockAddr)&(p->cm.sock.addr), &len)) < 0)
    return (handleError("accept", strerror(errno), -1));
  if (add_monitor(epoll, p->cm.sock.fd, p) < 0)
    return (handleError("add_monitor", "", p->cm.sock.fd));
  list_push_back_new(p->cm.out, "BIENVENUE\n", strlen("BIENVENUE\n") + 1);
  return (0);
}
