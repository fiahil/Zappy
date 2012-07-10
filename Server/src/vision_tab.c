/*
** vision_tab.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:13:29 2012 ulric lefevre
** Last update Tue Jul 10 14:57:38 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"def.h"
#include	"player.h"

static const	char *g_resources[8] =
  {
    " nourriture",
    " linemate",
    " deraumere",
    " sibur",
    " mendiane",
    " phiras",
    " thystame",
    NULL
  };

static const	int g_char_len[8] = {11, 9, 10, 6, 9, 7, 9, 0};

static const	t_u_pos g_vtab[4][81] =
  {
    {
      {0, 0},
      {-1, -1},
      {0, -1},
      {1, -1},
      {-2, -2},
      {-1, -2},
      {0, -2},
      {1, -2},
      {2, -2},
      {-3, -3},
      {-2, -3},
      {-1, -3},
      {0, -3},
      {1, -3},
      {2, -3},
      {3, -3},
      {-4, -4},
      {-3, -4},
      {-2, -4},
      {-1, -4},
      {0, -4},
      {1, -4},
      {2, -4},
      {3, -4},
      {4, -4},
      {-5, -5},
      {-4, -5},
      {-3, -5},
      {-2, -5},
      {-1, -5},
      {0, -5},
      {1, -5},
      {2, -5},
      {3, -5},
      {4, -5},
      {5, -5},
      {-6, -6},
      {-5, -6},
      {-4, -6},
      {-3, -6},
      {-2, -6},
      {-1, -6},
      {0, -6},
      {1, -6},
      {2, -6},
      {3, -6},
      {4, -6},
      {5, -6},
      {6, -6},
      {-7, -7},
      {-6, -7},
      {-5, -7},
      {-4, -7},
      {-3, -7},
      {-2, -7},
      {-1, -7},
      {0, -7},
      {1, -7},
      {2, -7},
      {3, -7},
      {4, -7},
      {5, -7},
      {6, -7},
      {7, -7},
      {-8, -8},
      {-7, -8},
      {-6, -8},
      {-5, -8},
      {-4, -8},
      {-3, -8},
      {-2, -8},
      {-1, -8},
      {0, -8},
      {1, -8},
      {2, -8},
      {3, -8},
      {4, -8},
      {5, -8},
      {6, -8},
      {7, -8},
      {8, -8},
    },
    {
      {0, 0},
      {1, -1},
      {1, 0},
      {1, 1},
      {2, -2},
      {2, -1},
      {2, 0},
      {2, 1},
      {2, 2},
      {3, -3},
      {3, -2},
      {3, -1},
      {3, 0},
      {3, 1},
      {3, 2},
      {3, 3},
      {4, -4},
      {4, -3},
      {4, -2},
      {4, -1},
      {4, 0},
      {4, 1},
      {4, 2},
      {4, 3},
      {4, 4},
      {5, -5},
      {5, -4},
      {5, -3},
      {5, -2},
      {5, -1},
      {5, 0},
      {5, 1},
      {5, 2},
      {5, 3},
      {5, 4},
      {5, 5},
      {6, -6},
      {6, -5},
      {6, -4},
      {6, -3},
      {6, -2},
      {6, -1},
      {6, 0},
      {6, 1},
      {6, 2},
      {6, 3},
      {6, 4},
      {6, 5},
      {6, 6},
      {7, -7},
      {7, -6},
      {7, -5},
      {7, -4},
      {7, -3},
      {7, -2},
      {7, -1},
      {7, 0},
      {7, 1},
      {7, 2},
      {7, 3},
      {7, 4},
      {7, 5},
      {7, 6},
      {7, 7},
      {8, -8},
      {8, -7},
      {8, -6},
      {8, -5},
      {8, -4},
      {8, -3},
      {8, -2},
      {8, -1},
      {8, 0},
      {8, 1},
      {8, 2},
      {8, 3},
      {8, 4},
      {8, 5},
      {8, 6},
      {8, 7},
      {8, 8},
    },
    {
      {0, 0},
      {1, 1},
      {0, 1},
      {-1, 1},
      {2, 2},
      {1, 2},
      {0, 2},
      {-1, 2},
      {-2, 2},
      {3, 3},
      {2, 3},
      {1, 3},
      {0, 3},
      {-1, 3},
      {-2, 3},
      {-3, 3},
      {4, 4},
      {3, 4},
      {2, 4},
      {1, 4},
      {0, 4},
      {-1, 4},
      {-2, 4},
      {-3, 4},
      {-4, 4},
      {5, 5},
      {4, 5},
      {3, 5},
      {2, 5},
      {1, 5},
      {0, 5},
      {-1, 5},
      {-2, 5},
      {-3, 5},
      {-4, 5},
      {-5, 5},
      {6, 6},
      {5, 6},
      {4, 6},
      {3, 6},
      {2, 6},
      {1, 6},
      {0, 6},
      {-1, 6},
      {-2, 6},
      {-3, 6},
      {-4, 6},
      {-5, 6},
      {-6, 6},
      {7, 7},
      {6, 7},
      {5, 7},
      {4, 7},
      {3, 7},
      {2, 7},
      {1, 7},
      {0, 7},
      {-1, 7},
      {-2, 7},
      {-3, 7},
      {-4, 7},
      {-5, 7},
      {-6, 7},
      {-7, 7},
      {8, 8},
      {7, 8},
      {6, 8},
      {5, 8},
      {4, 8},
      {3, 8},
      {2, 8},
      {1, 8},
      {0, 8},
      {-1, 8},
      {-2, 8},
      {-3, 8},
      {-4, 8},
      {-5, 8},
      {-6, 8},
      {-7, 8},
      {-8, 8},
    },
    {
      {0, 0},
      {-1, 1},
      {-1, 0},
      {-1, -1},
      {-2, 2},
      {-2, 1},
      {-2, 0},
      {-2, -1},
      {-2, -2},
      {-3, 3},
      {-3, 2},
      {-3, 1},
      {-3, 0},
      {-3, -1},
      {-3, -2},
      {-3, -3},
      {-4, 4},
      {-4, 3},
      {-4, 2},
      {-4, 1},
      {-4, 0},
      {-4, -1},
      {-4, -2},
      {-4, -3},
      {-4, -4},
      {-5, 5},
      {-5, 4},
      {-5, 3},
      {-5, 2},
      {-5, 1},
      {-5, 0},
      {-5, -1},
      {-5, -2},
      {-5, -3},
      {-5, -4},
      {-5, -5},
      {-6, 6},
      {-6, 5},
      {-6, 4},
      {-6, 3},
      {-6, 2},
      {-6, 1},
      {-6, 0},
      {-6, -1},
      {-6, -2},
      {-6, -3},
      {-6, -4},
      {-6, -5},
      {-6, -6},
      {-7, 7},
      {-7, 6},
      {-7, 5},
      {-7, 4},
      {-7, 3},
      {-7, 2},
      {-7, 1},
      {-7, 0},
      {-7, -1},
      {-7, -2},
      {-7, -3},
      {-7, -4},
      {-7, -5},
      {-7, -6},
      {-7, -7},
      {-8, 8},
      {-8, 7},
      {-8, 6},
      {-8, 5},
      {-8, 4},
      {-8, 3},
      {-8, 2},
      {-8, 1},
      {-8, 0},
      {-8, -1},
      {-8, -2},
      {-8, -3},
      {-8, -4},
      {-8, -5},
      {-8, -6},
      {-8, -7},
      {-8, -8},
    },
  };

static int	calc_nbcases(int lvl)
{
  int		i;
  int		nbcases;

  nbcases = 0;
  i = 0;
  while (i <= lvl)
    {
      nbcases += 1 + (i * 2);
      ++i;
    }
  return (nbcases - 1);
}

static t_square	get_cur_square(t_map map, t_player this, int i)
{
  return (map->map
	  [(this->pos.y + g_vtab[this->dir][i].y
	    + map->size_y * this->lvl) % map->size_y]
	  [(this->pos.x + g_vtab[this->dir][i].x
	    + map->size_x * this->lvl) % map->size_x]);
}

static int	get_size_look(t_map map, t_player this, int nbcases)
{
  int		i;
  int		j;
  int		count;
  t_square	cur;

  count = 3;
  i = 0;
  while (i <= nbcases)
    {
      cur = get_cur_square(map, this, i);
      count += (cur->players->size) * 7;
      j = -1;
      while (++j < LAST)
	count += (cur->inv.resources[j] * g_char_len[j]);
      ++i;
      if (i <= nbcases)
	++count;
    }
  return (count);
}

static void	add_look(t_square s, char **look)
{
  size_t	nb_player;
  size_t	i;
  int		j;

  if (s->players && s->players->size)
    {
      nb_player = get_nb_player(s);
      i = -1;
      while (++i < nb_player)
	*look = strcat(*look, " joueur");
    }
  i = FOOD;
  while (i < LAST)
    {
      j = -1;
      while (++j < s->inv.resources[i])
	*look = strcat(*look, g_resources[i]);
      ++i;
    }
}

char		*get_look(t_player this, t_map map)
{
  char		*look;
  int		i;
  int		nbcases;
  t_square	cur;
  int		len;

  nbcases = calc_nbcases(this->lvl);
  len = get_size_look(map, this, nbcases);
  if ((look = malloc(sizeof(*look) * len + 1)) == NULL)
    return (NULL);
  memset(look, 0, len + 1);
  look = strcat(look, "{");
  i = 0;
  while (i <= nbcases)
    {
      cur = get_cur_square(map, this, i);
      add_look(cur, &look);
      ++i;
      if (i <= nbcases)
	look = strcat(look, ",");
    }
  look = strcat(look, "}\n");
  return (look);
}
