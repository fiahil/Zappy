/*
** func_ctor_dtor_2.c for zappy bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server/src
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sun Jul  8 12:59:25 2012 ulric lefevre
** Last update Sun Jul  8 20:05:01 2012 ulric lefevre
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"def.h"
#include	"player.h"
#include	"handle_error.h"

void		dtor_egg(void *data)
{
  if (data)
    {
      if (((t_egg)data)->status && ((t_egg)data)->fetus)
	delete_player(((t_egg)data)->fetus);
      free(data);
    }
}
