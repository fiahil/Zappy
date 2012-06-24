/*
** handle_error.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:16:01 2012 ulric lefevre
** Last update Sun Jun 24 15:37:05 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<unistd.h>

int	handle_error(char *err_func, char *err_msg, int fd)
{
  fprintf(stderr, "Error: %s: %s\n", err_func, err_msg);
  if (fd > -1)
    close(fd);
  return (-1);
}
