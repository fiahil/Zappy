/*
** victory.c for zappy in /home/mart_i/Work/unix/Zappy/Server/src/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Mon Jul  2 15:03:00 2012 pierre martin
** Last update Fri Jul  6 16:06:16 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"stdout.h"
#include	"c_lists.h"
#include	"network.h"
#include	"algorithm.h"

static char*	g_end_msg = NULL;

static void	finishing(void *data, size_t len)
{
  t_player	player;

  (void)len;
  if (data)
    {
      player = *((t_player*)data);
      list_clear(player->cm.in);
      list_clear(player->cm.out);
      my_send(player->cm.sock.fd, "mort\n");
    }
}

static void	game_over(void *data, size_t len)
{
  t_graphic	m;

  (void)len;
  if (data)
    {
      m = (t_graphic)data;
      list_clear(m->cm.in);
      list_clear(m->cm.out);
      my_send(m->cm.sock.fd, g_end_msg);
    }
}

static char	*get_victorious(t_data_serv ds)
{
  t_iter	*it;
  t_iter	*it2;
  char		*ret;
  int		count;

  ret = NULL;
  count = 0;
  it = ds->teams->head;
  while (it && (count != 6))
    {
      count = 0;
      it2 = ds->player->head;
      while (it2 && (count != 6))
	{
	  if (!strcmp((*(t_player*)it2->data)->team, ((t_team)it->data)->name)
	      && (*(t_player*)it2->data)->lvl == 8)
	    ++count;
	  it2 = it2->next;
	}
      it = it->next;
    }
  if (count == 6)
    ret = ((t_team)it->data)->name;
  return (ret);
}

int		is_there_a_victorious(t_data_serv ds)
{
  char		*ret;
  char		*buf;

  if ((ret = get_victorious(ds)))
    {
      buf = NULL;
      asprintf(&buf, "L'equipe victorieuse est %s\n", ret);
      stdout_serv_status(buf, 0);
      free(buf);
      asprintf(&g_end_msg, "seg %s\n", ret);
      list_for_each(ds->player, &finishing);
      list_for_each(ds->monitor, &game_over);
      free(g_end_msg);
      return (0);
    }
  return (1);
}
