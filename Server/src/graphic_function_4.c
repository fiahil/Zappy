/*
** graphic_function_4.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:16:22 2012 ulric lefevre
** Last update Sun Jun 24 21:42:45 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>

#include	"graphic.h"
#include	"def.h"

void		edi(t_list *mn, int id)
{
  char		*str;

  str = NULL;
  asprintf(&str, "edi #%d\n", id);
  mn_push(mn, str);
  free(str);
}

void            ebo(t_list *mn, int id)
{
  char          *str;

  str = NULL;
  asprintf(&str, "ebo #%d\n", id);
  mn_push(mn, str);
  free(str);
}

void            eht(t_list *mn, int id)
{
  char          *str;

  str = NULL;
  asprintf(&str, "eht #%d\n", id);
  mn_push(mn, str);
  free(str);
}

void		enw(t_list *mn, int egg, int player, t_pos p)
{
  char		*str;

  str = NULL;
  asprintf(&str, "enw #%d #%d %d %d\n", egg, player, p->x, p->y);
  mn_push(mn, str);
  free(str);
}

void		pdi(t_list *mn, int id)
{
  char	*str;

  str = NULL;
  asprintf(&str, "pdi #%d\n", id);
  mn_push(mn, str);
  free(str);
}
