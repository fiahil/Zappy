/*
** network.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:14:54 2012 ulric lefevre
** Last update Mon Jun 25 15:02:26 2012 ulric lefevre
*/

#include	<errno.h>
#include	<netdb.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<netinet/in.h>
#include	<sys/socket.h>

#include	"def.h"
#include	"stdout.h"
#include	"network.h"
#include	"handle_error.h"
#include	"select_manager.h"

int	set_connection(t_data_serv data_serv, int port)
{
  int	op;

  stdout_serv_status("INITIALIZING CONNECTION:", 0);
  stdout_serv_status("\t\t\tInitializing socket.", 0);
  if ((data_serv->sock.fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    return (handle_error("socket", strerror(errno), data_serv->sock.fd));
  op = 1;
  stdout_serv_status("\t\t\tConfiguring socket.", 0);
  if (setsockopt(data_serv->sock.fd,
		 SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op)) < 0)
    return (handle_error("setsockopt", strerror(errno), data_serv->sock.fd));
  stdout_serv_status("\t\t\tBinding socket.", 0);
  data_serv->sock.addr.sin_family = AF_INET;
  data_serv->sock.addr.sin_port = htons(port);
  data_serv->sock.addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(data_serv->sock.fd, (t_sock_addr)&(data_serv->sock.addr),
	   sizeof(t_u_sock_addr_in)) < 0)
    return (handle_error("bind", strerror(errno), data_serv->sock.fd));
  stdout_serv_status("\t\t\tSetting listening state.", 0);
  if (listen(data_serv->sock.fd, 128) < 0)
    return (handle_error("listen", strerror(errno), data_serv->sock.fd));
  return (0);
}

int	accept_connection(t_select_manager sm, t_data_serv d_serv, t_player p)
{
  socklen_t	len;

  len = sizeof(p->cm.sock.addr);
  if ((p->cm.sock.fd = accept(d_serv->sock.fd,
			      (t_sock_addr)&(p->cm.sock.addr), &len)) < 0)
    return (handle_error("accept", strerror(errno), -1));
  select_add(sm, p->cm.sock.fd);
  p->cm.online = TRUE;
  list_push_back_new(p->cm.out, "BIENVENUE\n", strlen("BIENVENUE\n") + 1);
  return (0);
}

