/*
** string_manager.c for zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on Wed Jun  6 11:42:13 2012 benjamin businaro
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "def.h"

static const char *g_separator [] =
  {
    "\r\n",
    "\n",
    "\0128"
  };

static void	treatment_get_cmd(t_clientManager this, t_bool *clear, char **buf)
{
  char		*tmp;

  tmp = NULL;
  if (!(tmp = strstr((*buf), g_separator[this->mode])) && (*buf)[0] != '\0')
    {
      if (strlen(*buf) < (BUFFER_SIZE / 2))
	memcpy(this->stock + strlen(this->stock), (*buf), strlen(*buf));
      *clear = TRUE;
      printf("add to stock = [%s]\n", (*buf));
      fflush(0);
    }
  else if ((*buf)[0] != '\0')
    {
      tmp[0] = '\0';
      tmp += (strlen(g_separator[this->mode]));
      if (strlen((*buf)) < (BUFFER_SIZE / 2))
	memcpy(this->stock + strlen(this->stock), (*buf), strlen(*buf));
      list_push_back_new(this->in, this->stock, strlen(this->stock) + 1);
      memset(this->stock, '\0', BUFFER_SIZE);
      *buf = tmp;
    }
}

static void	treatment_first_cmd(t_clientManager this, char *buf)
{
  char *tmp;

  tmp = NULL;

  if ((tmp = strstr(buf, "\n")) && buf[0] != '\0')
    {
      if (tmp != buf)
	{
	  if (tmp[-1] == '\r')
	    this->mode = CRLF;
	  else
	    this->mode = LF;
	}
    }
}

void	get_commands(t_clientManager this, char *buf)
{
  t_bool	clear;

  assert(buf && this);
  clear = FALSE;
  if (this->mode == UNKNOW)
    treatment_first_cmd(this, buf);
  while (buf && buf[0] && !clear)
    treatment_get_cmd(this, &clear, &buf);
}
