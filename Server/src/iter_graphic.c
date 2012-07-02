#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "var_manager.h"
#include "select_manager.h"
#include "network.h"
#include "stdout.h"
#include "msgout_cmd.h"
#include "graphic.h"

static const t_u_parse_graph g_cmd[] =
  {
    {3, "msz", &msz_process},
    {3, "bct", &bct_process},
    {3, "mct", &mct_process},
    {3, "tna", &tna_process},
    {3, "ppo", &ppo_process},
    {3, "plv", &plv_process},
    {3, "pin", &pin_process},
    {3, "sgt", &sgt_process},
    {3, "sst", &sst_process},
    {0, NULL, NULL}
  };

static const char *g_separator[] =
  {
    "\r\n",
    "\n"
    "\0128"
  };

static void	print_stock(char **buf)
{
  char		*str;

  str = NULL;
  asprintf(&str, "add to stock = [%s]\n", (*buf));
  stdout_serv_status(str, 1);
  free(str);
}

static void	graphic_get_cmd(t_graphic this, t_bool *clear, char **buf)
{
  char	*tmp;

  tmp = NULL;
  if (!(tmp = strstr((*buf), g_separator[this->cm.mode])) && (*buf)[0] != '\0')
    {
      if (strlen(*buf) < (BUFFER_SIZE / 2))
  	memcpy(this->cm.stock + strlen(this->cm.stock), (*buf), strlen(*buf));
      *clear = TRUE;
      print_stock(buf);
    }
  else if ((*buf)[0] != '\0')
    {
      tmp[0] = '\0';
      tmp += (strlen(g_separator[this->cm.mode]));
      if (strlen((*buf)) < (BUFFER_SIZE / 2))
  	memcpy(this->cm.stock + strlen(this->cm.stock), (*buf), strlen(*buf));
      /* (this->cm.in->size < 10) ? */
      /* 	(list_push_back_new(this->cm.in, this->cm.stock, */
      /* 			    strlen(this->cm.stock) + 1)) : */
      /* 	(msgout_fail(this)); */
      list_push_back_new(this->cm.in, this->cm.stock, strlen(this->cm.stock) + 1);
      memset(this->cm.stock, '\0', BUFFER_SIZE);
      *buf = tmp;
    }
}

static void	graphic_first_cmd(t_graphic this, char *buf)
{
  char	*tmp;

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

void		get_graphic_commands(t_graphic this, char *buf)
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
  t_bool	flag;
  int		i;

  (void)ds;
  while (!(this->cm.in->empty))
    {
      i = -1;
      flag = FALSE;
      while (g_cmd[++i].cmd)
	if (!strncmp(list_front(this->cm.in), g_cmd[i].cmd, g_cmd[i].size))
	  flag = TRUE;
      if (!flag)
	printf("FAIL\n");
      else
	printf("CMD = %s - param = %s\n", g_cmd[i].cmd, list_front(this->cm.in) + 3);
      list_pop_front(this->cm.in);
    }
}

void		graphic_routine_input(t_data_serv ds, t_graphic this)
{
  char	*buf;

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

void		iter_graphic_rds(void *ptr, size_t s)
{
  t_select_manager	sm;
  t_data_serv		ds;

  (void)s;
  sm = get_select_manager(NULL);
  ds = get_data_serv(NULL);
  if (((t_graphic)ptr)->cm.online && select_r_isset(sm, ((t_graphic)ptr)->cm.sock.fd))
    graphic_routine_input(ds, ((t_graphic)ptr));
}
