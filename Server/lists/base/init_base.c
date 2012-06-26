/*
** init_base.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:24:15 2012 ulric lefevre
** Last update Sat Jun 23 20:24:16 2012 ulric lefevre
*/

#include	<string.h>
#include	<stdlib.h>
#include	"iter.h"

t_iter		*init_iter_def(t_iter *this)
{
  if (this)
    {
      this->data = NULL;
      this->len = 0;
      this->next = NULL;
      this->prev = NULL;
    }
  return (this);
}

t_iter		*init_iter_woa(t_iter *this, void *param)
{
  if (this)
    this->data = param;
  return (this);
}

t_iter		*init_iter_param(t_iter *this, void *param, size_t len)
{
  if (this)
    {
      if (param && len)
	{
	  this->data = malloc(len);
	  if (this->data)
	    {
	      this->data = memcpy(this->data, param, len);
	      this->len = len;
	    }
	}
    }
  return (this);
}
