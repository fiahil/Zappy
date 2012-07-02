/*
** victory.c for zappy in /home/mart_i/Work/unix/Zappy/Server/src/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Mon Jul  2 15:03:00 2012 pierre martin
** Last update Mon Jul  2 15:59:49 2012 pierre martin
*/

#define		_GNU_SOURCE
#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"c_lists.h"
#include	"network.h"
#include	"algorithm.h"

static char* g_end_msg = NULL;

static int	is_level_height(void *data, size_t len)
{
  t_player player;

  (void)len;
  if (data)
    {
      player = *((t_player*)data);
      if (player->lvl == 8)
	return (1);
    }
  return (0);
}

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
      m = *((t_graphic*)data);
      list_clear(m->cm.in);
      list_clear(m->cm.out);
      my_send(m->cm.sock.fd, g_end_msg);
    }
}

int	is_there_a_victorous(t_data_serv ds)
{
  t_player winner;

  if ((winner = *(t_player*)list_find_if(ds->player, &is_level_height)))
    {
      asprintf(&g_end_msg, "seg %s\n", winner->team);
      list_for_each(ds->player, &finishing);
      list_for_each(ds->monitor, &game_over);
      free(g_end_msg);
      return (0);
    }
  return (1);
}
