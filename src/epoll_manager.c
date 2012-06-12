/*
 * Fiahil
 * 07.06.2012
 */

#include <stdlib.h>
#include <sys/epoll.h>
#include <string.h>
#include <errno.h>
#include "handle_error.h"
#include "epoll_manager.h"
#include "network.h"
#include "server_routine.h"

int		init_epoll(t_epoll_manager epoll)
{
  if ((epoll->efd = epoll_create1(0)) < 0)
    return (handleError("epoll_create", strerror(errno), -1));
  return (0);
}

int		add_monitor(t_epoll_manager epoll, int fd, void *ptr)
{
  epoll->event.data.ptr = ptr;
  epoll->event.events = EPOLLIN | EPOLLOUT;
  if (epoll_ctl(epoll->efd, EPOLL_CTL_ADD, fd, &epoll->event) < 0)
    return (handleError("epoll_ctl", strerror(errno), -1));
  return (0);
}

int		del_monitor(t_epoll_manager epoll, int fd)
{
  if (epoll_ctl(epoll->efd, EPOLL_CTL_DEL, fd, (void*)-1) < 0)
    return (handleError("epoll_ctl", strerror(errno), -1));
  return (0);
}

int		update_monitor(t_epoll_manager epoll)
{
  int	ret;

  if ((ret = epoll_wait(epoll->efd, epoll->ev, 64/*TO MODIFY*/, 1000)) < -1)
    return (handleError("epoll_wait", strerror(errno), -1));
  return (ret);
}
