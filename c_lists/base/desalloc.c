/*
** desalloc.c for c_lists in /home/mart_i/Work/unix/irc-mart_i-magere_n/c_lists/base/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Thu Apr 19 09:21:42 2012 pierre martin
** Last update Thu Apr 19 09:23:16 2012 pierre martin
*/

#include	<stdlib.h>

#include	"iter.h"

void		delete_iter(t_iter *this, t_dtor dtor)
{
  if (this)
    {
      if (this->data)
	dtor(this->data);
      free(this);
    }
}

void		delete_iters(t_iter *this, t_dtor dtor)
{
  if (this)
    {
      if (this->next)
	delete_iters(this->next, dtor);
      delete_iter(this, dtor);
    }
}
