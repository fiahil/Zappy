/*
 * Fiahil
 * 15.06.2012
 */

#include	<errno.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/time.h>

#include	"def.h"
#include	"handle_error.h"
#include	"select_manager.h"

static t_select_manager		g_sm = 0;

static void	select_set(void *ptr, size_t s)
{
  (void)s;
  if ((*(t_player*)ptr)->cm.online)
  {
    FD_SET((*(t_player*)ptr)->cm.sock.fd, &g_sm->rds);
    if (!(*(t_player*)ptr)->cm.out->empty)
      FD_SET((*(t_player*)ptr)->cm.sock.fd, &g_sm->wds);
  }
}

static void	select_cmp(void *ptr, size_t s)
{
  (void)s;
  if ((*(t_player*)ptr)->cm.sock.fd > g_sm->max_fd)
    g_sm->max_fd = (*(t_player*)ptr)->cm.sock.fd;
}

void		select_del(t_data_serv ds, t_select_manager sm, int fd)
{
  g_sm = sm;
  if (fd == sm->max_fd)
    list_for_each(ds->player, &select_cmp);
}

void		select_manager(t_data_serv ds, t_select_manager sm)
{
  g_sm = sm;
  FD_ZERO(&sm->rds);
  FD_ZERO(&sm->wds);
  FD_SET(ds->sock.fd, &sm->rds);
  list_for_each(ds->player, &select_set);
  if (select(sm->max_fd + 1, &sm->rds, NULL, NULL, &sm->timeout) < 0)
    handleError("select", strerror(errno), -1);
}
