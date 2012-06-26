/*
** alloc.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:24:56 2012 ulric lefevre
** Last update Mon Jun 25 18:20:10 2012 pierre martin
*/

#include <stdlib.h>
#include "c_lists.h"

t_list	*init_list(t_list *this, t_ctor ctor, t_dtor dtor, t_copy cpy)
{
  if (this)
    {
      this->empty = 1;
      this->size = 0;
      this->ctor = ctor;
      this->dtor = dtor;
      this->copy = cpy;
      this->head = NULL;
      this->tail = NULL;
    }
  return (this);
}

t_list		*new_list(t_ctor ctor, t_dtor dtor, t_copy copy)
{
  t_list	*new;

  new = malloc(sizeof(*new));
  return (init_list(new, ctor, dtor, copy));
}

void		delete_list(t_list *this)
{
  if (this)
    {
      delete_iters(this->head, this->dtor);
      free(this);
    }
}

void		list_clear(t_list *this)
{
  if (this)
    {
      delete_iters(this->head, this->dtor);
      this->head = NULL;
      this->tail = NULL;
      this->size = 0;
      this->empty = 1;
    }
}
