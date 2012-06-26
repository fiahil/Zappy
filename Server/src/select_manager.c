/*
** select_manager.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:14:14 2012 ulric lefevre
** Last update Tue Jun 26 11:29:18 2012 pierre martin
*/

#include	<errno.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/time.h>

#include	"def.h"
#include	"algorithm.h"
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

static void	select_mset(void *ptr, size_t s)
{
  (void)s;
  if (((t_graphic)ptr)->cm.online)
  {
    FD_SET(((t_graphic)ptr)->cm.sock.fd, &g_sm->rds);
    if (!((t_graphic)ptr)->cm.out->empty)
      FD_SET(((t_graphic)ptr)->cm.sock.fd, &g_sm->wds);
  }
}

static void	select_cmp(void *ptr, size_t s)
{
  (void)s;
  if ((*(t_player*)ptr)->cm.online && (*(t_player*)ptr)->cm.sock.fd > g_sm->max_fd)
    g_sm->max_fd = (*(t_player*)ptr)->cm.sock.fd;
}

static void	select_mcmp(void *ptr, size_t s)
{
  (void)s;
  if (((t_graphic)ptr)->cm.online && ((t_graphic)ptr)->cm.sock.fd > g_sm->max_fd)
    g_sm->max_fd = ((t_graphic)ptr)->cm.sock.fd;
}

void		select_del(t_data_serv ds, int fd)
{
  if (fd == g_sm->max_fd)
  {
    g_sm->max_fd = ds->sock.fd;
    list_for_each(ds->player, &select_cmp);
    list_for_each(ds->monitor, &select_mcmp);
  }
}

void		select_manager(t_data_serv ds, t_select_manager sm)
{
  g_sm = sm;
  FD_ZERO(&sm->rds);
  FD_ZERO(&sm->wds);
  FD_SET(ds->sock.fd, &sm->rds);
  list_for_each(ds->player, &select_set);
  list_for_each(ds->monitor, &select_mset);
  if (select(sm->max_fd + 1, &sm->rds, &sm->wds, NULL, &sm->timeout) < 0)
    handle_error("select", strerror(errno), -1);
}
