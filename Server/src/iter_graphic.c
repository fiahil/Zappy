/*
** iter_graphic.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Wed Jul  4 13:55:31 2012 ulric lefevre
** Last update Wed Jul  4 13:55:46 2012 ulric lefevre
*/

#define _GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"var_manager.h"
#include	"select_manager.h"
#include	"network.h"
#include	"stdout.h"
#include	"msgout_cmd.h"
#include	"graphic.h"
#include	"graphic_tools.h"

static const t_u_parse_graph g_cmd[] =
  {
    {3, "msz", &msz_process},
    {3, "mct", &mct_process},
    {3, "tna", &tna_process},
    {3, "sgt", &sgt_process},
    {4, "bct ", &bct_process},
    {4, "ppo ", &ppo_process},
    {4, "plv ", &plv_process},
    {4, "pin ", &pin_process},
    {4, "sst ", &sst_process},
    {0, NULL, NULL}
  };

static const char *g_separator [] =
  {
    "\r\n",
    "\n",
    "\0128"
  };

static void	graphic_get_cmd(t_graphic this, t_bool *clear, char **buf)
{
  char		*tmp;

  tmp = NULL;
  if (!(tmp = strstr((*buf), g_separator[this->cm.mode])) && (*buf)[0] != '\0')
    {
      if (strlen(*buf) < (BUFFER_SIZE / 2))
      	memcpy(this->cm.stock + strlen(this->cm.stock), (*buf), strlen(*buf));
      *clear = TRUE;
    }
  else if ((*buf)[0] != '\0')
    {
      tmp[0] = '\0';
      tmp += (strlen(g_separator[this->cm.mode]));
      if (strlen((*buf)) < (BUFFER_SIZE / 2))
  	memcpy(this->cm.stock + strlen(this->cm.stock), (*buf), strlen(*buf));
      list_push_back_new(this->cm.in, this->cm.stock, strlen(this->cm.stock) + 1);
      memset(this->cm.stock, '\0', BUFFER_SIZE);
      *buf = tmp;
    }
}

static void	graphic_first_cmd(t_graphic this, char *buf)
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

static void	get_graphic_commands(t_graphic this, char *buf)
{
  t_bool	clear;

  clear = FALSE;
  if (this->cm.mode == UNKNOW)
    graphic_first_cmd(this, buf);
  while (buf && buf[0] && !clear)
    graphic_get_cmd(this, &clear, &buf);
}

static void	graphic_process(t_graphic this, t_data_serv ds)
{
  char		*tmp;
  int		i;

  (void)ds;
  while (!(this->cm.in->empty))
    {
      i = -1;
      tmp = strdup(list_front(this->cm.in));
      while (g_cmd[++i].cmd && strncmp(list_front(this->cm.in), g_cmd[i].cmd, g_cmd[i].size));
      if (g_cmd[i].cmd)
	if (((i >= 4 && i <= 8) && ((char *)list_front(this->cm.in))[3]) ^
	    ((i >= 0 && i <= 3) && !((char *)list_front(this->cm.in))[3]))
	  (g_cmd[i].func)(this, get_params(tmp + 3), ds);
      free(tmp);
      list_pop_front(this->cm.in);
    }
}

void		graphic_routine_input(t_data_serv ds, t_graphic this)
{
  char		*buf;

  if ((buf = my_receive(this->cm.sock.fd)) == (char*)(-1))
    {
      this->cm.online = FALSE;
      close(this->cm.sock.fd);
      select_del(ds, this->cm.sock.fd);
      // stdout "disconnected" ?
      return ;
    }
  get_graphic_commands(this, buf);
  graphic_process(this, ds);
  free(buf);
}
