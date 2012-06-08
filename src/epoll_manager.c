/*
 * Fiahil
 * 07.06.2012
 */

#include <stdlib.h>
#include <sys/epoll.h>
#include "handle_error.h"
#include "epoll_manager.h"

static int			g_fd = 0;
static struct epoll_event	*g_events = NULL;

void		init_epoll()
{
  g_fd = epoll_create1(0);
  if (g_fd == -1)
    handleError("epoll_create", "fail", 0);
}

void		add_monitor(int fd)
{
  struct epoll_event	event;

  event.events = EPOLLIN | EPOLLOUT;
  event.data.fd = fd;
  if (epoll_ctl(g_fd, EPOLL_CTL_ADD, fd, &event) == -1)
    handleError("epoll_ctl", "add", 0);
}

void		del_monitor(int fd)
{
  if (epoll_ctl(g_fd, EPOLL_CTL_DEL, fd, (void*)-1) == -1)
    handleError("epoll_ctl", "del", 0);
}

void		update_monitor()
{
  if (epoll_wait(g_fd, g_events, 10000, 0) == -1)
    handleError("epoll_wait", "fail", 0);
}
