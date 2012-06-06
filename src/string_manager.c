/*
** string_manager.c for zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on Wed Jun  6 11:42:13 2012 benjamin businaro
** Last update Wed Jun  6 16:58:36 2012 benjamin businaro
*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "def.h"

static const char *g_separator [] =
  {
    "\r\n",
    "\n"
  };

void	get_commands(t_clientManager this, char *buf)
{
  char *tmp;
  t_bool clear;

  /* assert(!buf || !this); */
  clear = FALSE;
  while (buf && buf[0] && !clear)
    {
      tmp = NULL;
      fflush(0);
      if (!(tmp = strstr(buf, g_separator[this->mode])) && buf[0] != '\0')
	{
	  fflush(0);
	  if (strlen(buf) < 2048)
	    memcpy(this->stock + strlen(this->stock), buf, strlen(buf));
	  clear = TRUE;
	}
      else if (buf[0] != '\0')
	{
	  tmp[0] = '\0';
	  unsigned int i = 0;
	  while (i < strlen(g_separator[this->mode]))
	    {
	      ++tmp;
	      ++i;
	    }
	  if (strlen(buf) < 2048)
	    memcpy(this->stock + strlen(this->stock), buf, strlen(buf));
	  // add des stock a la list des commandes
	  printf("after split and concat stock = %s\n", this->stock);
	  fflush(0);
	  memset(this->stock, '\0', BUFFER_SIZE);
	  buf = tmp;
	}
    }
}
