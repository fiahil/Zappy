/*
** string_manager.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:13:51 2012 ulric lefevre
** Last update Sat Jun 30 13:50:06 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<assert.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"msgout_cmd.h"

static const char *g_separator [] =
  {
    "\r\n",
    "\n",
    "\0128"
  };

static void	treatment_get_cmd(t_player this, t_bool *clear, char **buf)
{
  char		*tmp;

  tmp = NULL;
  if (!(tmp = strstr((*buf), g_separator[this->cm.mode])) && (*buf)[0] != '\0')
    {
      if (strlen(*buf) < (BUFFER_SIZE / 2))
	memcpy(this->cm.stock + strlen(this->cm.stock), (*buf), strlen(*buf));
      *clear = TRUE;
      printf("add to stock = [%s]\n", (*buf));
    }
  else if ((*buf)[0] != '\0')
    {
      tmp[0] = '\0';
      tmp += (strlen(g_separator[this->cm.mode]));
      if (strlen((*buf)) < (BUFFER_SIZE / 2))
	memcpy(this->cm.stock + strlen(this->cm.stock), (*buf), strlen(*buf));
      if (this->cm.in->size < 10)
	list_push_back_new(this->cm.in, this->cm.stock,
			   strlen(this->cm.stock) + 1);
      else
	msgout_fail(this);
      memset(this->cm.stock, '\0', BUFFER_SIZE);
      *buf = tmp;
    }
}

static void	treatment_first_cmd(t_player this, char *buf)
{
  char		*tmp;

  tmp = NULL;

  if ((tmp = strstr(buf, "\n")) && buf[0] != '\0')
    {
      if (tmp != buf)
	{
	  if (tmp[-1] == '\r')
	    this->cm.mode = CRLF;
	  else
	    this->cm.mode = LF;
	}
    }
}

void		get_commands(t_player this, char *buf)
{
  t_bool	clear;

  assert(buf && this);
  clear = FALSE;
  if (this->cm.mode == UNKNOW)
    treatment_first_cmd(this, buf);
  while (buf && buf[0] && !clear)
    treatment_get_cmd(this, &clear, &buf);
}
