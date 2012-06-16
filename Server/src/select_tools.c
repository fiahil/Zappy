/*
** select_tools.c for zappy in /home/mart_i/Work/unix/Zappy/Server/src/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Sat Jun 16 16:45:56 2012 pierre martin
*/

#include	"def.h"
#include	"select_manager.h"

void		select_add(t_select_manager sm, int fd)
{
  if (fd > sm->max_fd)
    sm->max_fd = fd;
}

t_bool		select_isset(t_select_manager sm, int fd)
{
  return (FD_ISSET(fd, &sm->rds) ? TRUE : FALSE);
}

