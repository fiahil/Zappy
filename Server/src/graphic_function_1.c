/*
** graphic_function_1.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:16:36 2012 ulric lefevre
** Last update Sun Jun 24 21:43:21 2012 ulric lefevre
*/

#define		_GNU_SOURCE

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>

#include	"graphic.h"
#include	"def.h"

void		sbp(t_list *mn)
{
  mn_push(mn, "sbp\n");
}

void		suc(t_list *mn)
{
  mn_push(mn, "suc\n");
}

void		smg(t_list *mn, char const *msg)
{
  char		*str;

  str = NULL;
  asprintf(&str, "smg %s\n", msg);
  mn_push(mn, str);
  free(str);
}

void		seg(t_list *mn, int team)
{
  char		*str;

  str = NULL;
  asprintf(&str, "seg %d\n", team);
  mn_push(mn, str);
  free(str);
}

void		pgt(t_list *mn, int id, int res)
{
  char	*str;

  str = NULL;
  asprintf(&str, "pgt #%d %d\n", id, res);
  mn_push(mn, str);
  free(str);
}
