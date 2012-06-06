
#include	<stdio.h>
#include	<stdlib.h>
#include	"select_manager.h"

static t_select	fds;

static void     init_select(t_clientManager *clients)
{
  int		i;

  FD_ZERO(&fds.readfds);
  FD_ZERO(&fds.writefds);
  i = 0;
  while (clients && clients[i])
    {
      if (clients[i]->online)
	{
	  FD_SET(clients[i]->sock->fd, &fds.readfds);
	  FD_SET(clients[i]->sock->fd, &fds.writefds);
	}
      ++i;
    }
}

int		select_isset(int fd, t_rw flag)
{
  if (flag == READ)
    return (FD_ISSET(fd, &fds.readfds) ? 1 : 0);
  else
    return (FD_ISSET(fd, &fds.writefds) ? 1 : 0);
}

void		select_manager(t_clientManager *clients)
{
  init_select(clients);
  select(get_max_fd() + 1, &fds.readfds, &fds.writefds, NULL, NULL);
}
