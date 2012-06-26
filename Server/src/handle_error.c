/*
** handle_error.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:16:01 2012 ulric lefevre
** Last update Sun Jun 24 21:42:30 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

int	handle_error(char *err_func, char *err_msg, int fd)
{
  fprintf(stderr, "Error: %s: %s\n", err_func, err_msg);
  if (fd > -1)
    close(fd);
  return (-1);
}

int	handle_error_ft(char *err_func, char *err_msg, int fd)
{
  fprintf(stderr, "Error: %s: %s\n", err_func, err_msg);
  if (fd > -1)
    close(fd);
  exit(EXIT_FAILURE);
  return (-1);
}

void	handle_error_nr(char *err, char *msg)
{
  fprintf(stderr, "Error: %s: %s\n", err, msg);
}

void	crash_error(char *err, char *msg)
{
  fprintf(stderr, "Error: %s: %s\n", err, msg);
  exit(EXIT_FAILURE);
}
