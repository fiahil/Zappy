/*
** alloc.c for c_lists in /home/mart_i/Work/unix/irc-mart_i-magere_n/c_lists/lists_ops/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Tue Apr 17 23:13:14 2012 pierre martin
** Last update Thu Jun  7 10:38:46 2012 pierre martin
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
