/*
** pqueue_tools.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:23:51 2012 ulric lefevre
** Last update Sat Jun 23 20:23:53 2012 ulric lefevre
*/

#include	<stdlib.h>

#include	"pqueue.h"
#include	"algorithm.h"

int	pqueue_empty(t_pqueue *this)
{
  return (this->queue.empty);
}

size_t	pqueue_size(t_pqueue *this)
{
  return (this->queue.size);
}

void	pqueue_reorder(t_pqueue *this)
{
  list_sort(&(this->queue), this->cmp);
}

void	delete_pqueue(t_pqueue *this)
{
  if (this)
    {
      delete_iters(this->queue.head, NULL);
      free(this);
    }
}
