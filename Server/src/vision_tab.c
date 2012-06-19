
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"def.h"

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

void		add_to_str(char **dest, const char *src)
{
  char		*tmp;

  if (dest && *dest)
    {
      if ((*dest = realloc(*dest, strlen(*dest) + strlen(src) + 1)) == NULL)
	return ;
      tmp = strdup(strcat(*dest, src));
      free(*dest);
      *dest = tmp;
    }
}

void		add_players(t_square s, char **look)
{
  size_t	i;

  if (s->players && s->players->size)
    {
      i = 0;
      while (i < s->players->size)
	{
	  add_to_str(look, " joueur");
	  ++i;
	}
    }
}

void		add_resources(t_square s, char **look)
{
  int		i;
  int		j;

  i = FOOD;
  while (i < LAST)
    {
      j = 0;
      while (j < s->inv.resources[i])
	{
	  add_to_str(look, g_resources[i]);
	  ++j;
	}
      ++i;
    }
}

char		*get_look(t_player this, t_map map)
{
  char		*look;
  int		i;
  int		nbcases;
  t_square	cur;

  nbcases = calc_nbcases(this->lvl);
  look = strdup("{");
  i = 0;
  while (i <= nbcases)
    {
      cur = map->map[(this->pos.y + g_vtab[this->dir][i].y
		      + map->size_y) % map->size_y]
	[(this->pos.x + g_vtab[this->dir][i].x
	  + map->size_x) % map->size_x];
      add_players(cur, &look);
      add_resources(cur, &look);
      ++i;
      if (i <= nbcases)
	add_to_str(&look, ",");
    }
  add_to_str(&look, "}\n");
  return (look);
}
