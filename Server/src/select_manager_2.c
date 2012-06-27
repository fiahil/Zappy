/*
** select_manager_2.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Tue Jun 26 16:01:18 2012 ulric lefevre
** Last update Tue Jun 26 16:14:50 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"algorithm.h"
#include	"var_manager.h"

static t_select_manager		g_sm = 0;

static void	select_cmp(void *ptr, size_t s)
{
  (void)s;
  if ((*(t_player*)ptr)->cm.online
      && (*(t_player*)ptr)->cm.sock.fd > g_sm->max_fd)
    g_sm->max_fd = (*(t_player*)ptr)->cm.sock.fd;
}

static void	select_mcmp(void *ptr, size_t s)
{
  (void)s;
  if (((t_graphic)ptr)->cm.online
      && ((t_graphic)ptr)->cm.sock.fd > g_sm->max_fd)
    g_sm->max_fd = ((t_graphic)ptr)->cm.sock.fd;
}

void		select_del(t_data_serv ds, int fd)
{
  g_sm = get_select_manager(NULL);
  if (fd == g_sm->max_fd)
  {
    g_sm->max_fd = ds->sock.fd;
    list_for_each(ds->player, &select_cmp);
    list_for_each(ds->monitor, &select_mcmp);
  }
}
