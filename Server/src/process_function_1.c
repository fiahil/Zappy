/*
** process_function_1.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:14:32 2012 ulric lefevre
** Last update Sat Jun 23 20:14:33 2012 ulric lefevre
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "msgout_cmd.h"
#include "process_function.h"

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

t_bool	look_process(t_player this, char *data, t_data_serv info)
{
  char		*look;
  t_map		map;

  (void)data;
  (void)info;
  map = get_map(NULL);
  look = get_look(this, map);
  msgout_voir(this->cm.out, look);
  free(look);
  return (TRUE);
}

t_bool	take_process(t_player this, char *data, t_data_serv info)
{
  t_map		map;
  char		*log;
  int		i;
  t_bool	is_done;

  (void)info;
  i = -1;
  is_done = FALSE;
  while (g_resources[++i] && strcmp(data, g_resources[i]));
  //system("clear"); // ENABLE THIS LINE FOR "REALTIME" MAP DISPLAY
  if (g_resources[i] &&
      (map = get_map(NULL))->map[this->pos.y][this->pos.x]->inv.resources[i])
    {
      --map->map[this->pos.y][this->pos.x]->inv.resources[i];
      ++this->inv.resources[i];
      asprintf(&log, "Taking %s !\n", data);
      is_done = TRUE;
    }
  else
    asprintf(&log, "No %s on this square !\n", data);
  list_push_back_new(this->cm.out, log, strlen(log) + 1);
  free(log);
  msgout_prend_objet(this->cm.out, is_done);
  //display((map = get_map(NULL))); // ENABLE THIS LINE FOR "REALTIME" MAP DISPLAY
  return (TRUE);
}

t_bool	drop_process(t_player this, char *data, t_data_serv info)
{
  t_map		map;
  char		*log;
  int		i;
  t_bool	is_done;

  (void)info;
  i = -1;
  is_done = FALSE;
  while (g_resources[++i] && strcmp(data, g_resources[i]));
  //system("clear"); // ENABLE THIS LINE FOR "REALTIME" MAP DISPLAY
  if (g_resources[i] && this->inv.resources[i])
    {
      ++(map = get_map(NULL))->map[this->pos.y][this->pos.x]->inv.resources[i];
      --this->inv.resources[i];
      asprintf(&log, "Dropping %s !\n", data);
      is_done = TRUE;
    }
  else
    asprintf(&log, "No %s in inventory !\n", data);
  list_push_back_new(this->cm.out, log, strlen(log) + 1);
  msgout_pose_objet(this->cm.out, is_done);
  free(log);
  //display((map = get_map(NULL))); // ENABLE THIS LINE FOR "REALTIME" MAP DISPLAY
  return (TRUE);
}

t_bool  right_process(t_player this, char *data, t_data_serv info)
{
  (void)data;
  (void)info;
  if (this->dir == WEST)
    this->dir = NORTH;
  else
    this->dir += 1;
  msgout_droite(this->cm.out);
  return (TRUE);
}

t_bool  left_process(t_player this, char *data, t_data_serv info)
{
  (void)data;
  (void)info;
  if (this->dir == NORTH)
    this->dir = WEST;
  else
    this->dir -= 1;
  msgout_gauche(this->cm.out);
  return (TRUE);
}
