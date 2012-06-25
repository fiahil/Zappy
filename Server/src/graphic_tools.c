/*
** graphic_tools.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:16:08 2012 ulric lefevre
** Last update Sun Jun 24 21:41:25 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<string.h>
#include	<assert.h>

#include	"select_manager.h"
#include	"graphic.h"
#include	"network.h"
#include	"def.h"
#include	"var_manager.h"

static char 	*g_msg;

static void	iter_monitor(void *ptr, size_t s)
{
  (void)s;
  if (!((t_graphic)ptr)->cm.out->empty &&
      select_w_isset(get_select_manager(NULL), ((t_graphic)ptr)->cm.sock.fd))
   {
     my_send(((t_graphic)ptr)->cm.sock.fd, list_front(((t_graphic)ptr)->cm.out));
     list_pop_front(((t_graphic)ptr)->cm.out);
   }
}

static void	push_to_monitor(void *ptr, size_t s)
{
  (void)s;
  list_push_back_new(((t_graphic)ptr)->cm.out, g_msg, strlen(g_msg) + 1);
}

void		mn_push(t_list *mn, char *msg)
{
  g_msg = msg;
  list_for_each(mn, &push_to_monitor);
}

void		mn_out(t_list *mn)
{
  list_for_each(mn, &iter_monitor);
}

void		mn_rep(t_graphic mn, char *msg)
{
  list_push_back_new(mn->cm.out, msg, strlen(msg) + 1);
}
