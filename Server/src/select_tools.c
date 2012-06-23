/*
** select_tools.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:14:08 2012 ulric lefevre
** Last update Sat Jun 23 20:14:08 2012 ulric lefevre
*/

#include	"def.h"
#include	"select_manager.h"

void		select_add(t_select_manager sm, int fd)
{
  if (fd > sm->max_fd)
    sm->max_fd = fd;
}

t_bool		select_r_isset(t_select_manager sm, int fd)
{
  return (FD_ISSET(fd, &sm->rds) ? TRUE : FALSE);
}

t_bool          select_w_isset(t_select_manager sm, int fd)
{
  return (FD_ISSET(fd, &sm->wds) ? TRUE : FALSE);
}
