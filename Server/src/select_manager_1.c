/*
** select_manager.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:14:14 2012 ulric lefevre
** Last update Fri Jul  6 13:03:15 2012 ulric lefevre
*/

#include	<errno.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/time.h>

#include	"def.h"
#include	"algorithm.h"
#include	"var_manager.h"
#include	"handle_error.h"
#include	"select_manager.h"

static void	select_set(void *ptr, size_t s)
{
  t_select_manager sm;

  (void)s;
  sm = get_select_manager(NULL);
  if ((*(t_player*)ptr)->cm.online)
  {
    (*(t_player*)ptr)->cm.read = TRUE;
    FD_SET((*(t_player*)ptr)->cm.sock.fd, &sm->rds);
    if (!(*(t_player*)ptr)->cm.out->empty)
      FD_SET((*(t_player*)ptr)->cm.sock.fd, &sm->wds);
  }
}

static void	select_mset(void *ptr, size_t s)
{
  t_select_manager sm;

  (void)s;
  sm = get_select_manager(NULL);
  if (((t_graphic)ptr)->cm.online)
  {
    FD_SET(((t_graphic)ptr)->cm.sock.fd, &sm->rds);
    if (!((t_graphic)ptr)->cm.out->empty)
      FD_SET(((t_graphic)ptr)->cm.sock.fd, &sm->wds);
  }
}

void		select_manager(t_data_serv ds, t_select_manager sm)
{
  get_select_manager(sm);
  FD_ZERO(&sm->rds);
  FD_ZERO(&sm->wds);
  FD_SET(ds->sock.fd, &sm->rds);
  list_for_each(ds->player, &select_set);
  list_for_each(ds->monitor, &select_mset);
  if (sm->timeout.tv_sec < 0)
    sm->timeout.tv_sec = 0;
  if (sm->timeout.tv_sec == 0 && sm->timeout.tv_usec <= 0)
    sm->timeout.tv_usec = 5;
  if (select(sm->max_fd + 1, &sm->rds, &sm->wds, NULL, &sm->timeout) < 0)
    handle_error("select", strerror(errno), -1);
}
