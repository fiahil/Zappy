/*
** desalloc.c for zappy_bibicy* in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:24:18 2012 ulric lefevre
** Last update Tue Jul 10 10:14:19 2012 ulric lefevre
*/

#include	<stdlib.h>

#include	"iter.h"

void		delete_iter(t_iter *this, t_dtor dtor)
{
  if (this)
    {
      if (this->data && dtor)
	dtor(this->data);
      else if (this->data)
	free(this->data);
      free(this);
    }
}

void		delete_iters(t_iter *this, t_dtor dtor)
{
  t_iter	*it;

  while (this)
    {
      it = this->next;
      delete_iter(this, dtor);
      this = it;
    }
}
