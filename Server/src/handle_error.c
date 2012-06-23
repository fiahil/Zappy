/*
** error.c for zappy in /home/mart_i/Work/unix/Zappy/src/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Wed Jun  6 20:45:17 2012 pierre martin
*/

#include	<stdio.h>
#include	<unistd.h>

#include	"handle_error.h"

int	handle_error(char *err_func, char *err_msg, int fd)
{
  fprintf(stderr, "Error: %s: %s\n", err_func, err_msg);
  if (fd > -1)
    close(fd);
  return (-1);
}
