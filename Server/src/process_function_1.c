/*
** process_function.c for Zappy in /home/busina_b/Projet/Zappy-Unix/Zappy/src/
** 
** Made by benjamin businaro
** Login   <busina_b@epitech.net>
** 
** Started on Thu Jun  7 14:12:59 2012 benjamin businaro
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "process_function.h"
#include "map.h"
#include "msgout_cmd.h"

static char	*g_resources[] =
  {
    "nourriture",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
    NULL
  };

t_bool		look_process_function(t_player this, char *data)
{
  (void)data;
  list_push_back_new(this->cm.out, "I look at this !\n", strlen("I look at this !\n") + 1);

  return (TRUE);
}

t_bool		inventory_process_function(t_player this, char *data)
{
  (void)data;
  list_push_back_new(this->cm.out, "I check my inventory !\n", strlen("I check my inventory !\n") + 1);
  msgout_inventaire(this->cm.out, this->inv);
  return (TRUE);
}

t_bool		take_process_function(t_player this, char *data)
{
  t_map	map;
  char	*log;
  int	i;

  i = -1;
  while (g_resources[++i] && strcmp(data, g_resources[i]));
  system("clear"); // ENABLE THIS LINE FOR "REALTIME" MAP DISPLAY
  if (g_resources[i] && (map = get_map(NULL))->map[this->pos.y][this->pos.x]->inv.resources[i])
    {
      --map->map[this->pos.y][this->pos.x]->inv.resources[i];
      ++this->inv.resources[i];
      asprintf(&log, "Taking %s !\n", data);
    }
  else
    asprintf(&log, "No %s on this square !\n", data);
  list_push_back_new(this->cm.out, log, strlen(log));
  display((map = get_map(NULL))); // ENABLE THIS LINE FOR "REALTIME" MAP DISPLAY
  return (TRUE);
}

t_bool		drop_process_function(t_player this, char *data)
{
  t_map	map;
  char	*log;
  int	i;

  i = -1;
  while (g_resources[++i] && strcmp(data, g_resources[i]));
  system("clear"); // ENABLE THIS LINE FOR "REALTIME" MAP DISPLAY
  if (g_resources[i] && this->inv.resources[i])
    {
      ++(map = get_map(NULL))->map[this->pos.y][this->pos.x]->inv.resources[i];
      --this->inv.resources[i];
      asprintf(&log, "Dropping %s !\n", data);
      list_push_back_new(this->cm.out, "OK\n", 3);
    }
  else
    asprintf(&log, "No %s in inventory !\n", data);
  list_push_back_new(this->cm.out, log, strlen(log));
  display((map = get_map(NULL))); // ENABLE THIS LINE FOR "REALTIME" MAP DISPLAY
  return (TRUE);
}

t_bool		expulse_process_function(t_player this, char *data)
{
  (void)data;
  list_push_back_new(this->cm.out, "I expulse !\n", strlen("I expulse !\n") + 1);

  return (TRUE);
}
