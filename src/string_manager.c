/*
** string_manager.c for zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on Wed Jun  6 11:42:13 2012 benjamin businaro
** Last update Wed Jun  6 22:11:26 2012 benjamin businaro
*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "def.h"

static const char *g_separator [] =
  {
    "\r\n",
    "\n"
  };

static void	treatment_get_cmd(t_clientManager this, t_bool *clear, char **buf)
{
  char		*tmp;

      tmp = NULL;
  if (!(tmp = strstr((*buf), g_separator[this->mode])) && (*buf)[0] != '\0')
    {
      if (strlen((*buf)) < (BUFFER_SIZE / 2))
	memcpy(this->stock + strlen(this->stock), buf, strlen((*buf)));
      (*clear) = TRUE;
    }
  else if (buf[0] != '\0')
    {
      tmp[0] = '\0';
      tmp += (strlen(g_separator[this->mode]) * sizeof(tmp));
      if (strlen((*buf)) < (BUFFER_SIZE / 2))
	memcpy(this->stock + strlen(this->stock), buf, strlen((*buf)));
      list_push_back_new(&this->in, this->stock, strlen(this->stock) + 1);
      printf("after split and concat stock = %s\n", this->stock);
      fflush(0); //TODO
      memset(this->stock, '\0', BUFFER_SIZE);
      (*buf) = tmp;
    }
}

void	get_commands(t_clientManager this, char *buf)
{
  t_bool	clear;

  assert(buf && this);
  clear = FALSE;
  while (buf && buf[0] && !clear)
    treatment_get_cmd(this, &clear, &buf);
}
