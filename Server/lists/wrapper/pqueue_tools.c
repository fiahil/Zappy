/*
** pqueue_tools.c for pqueue in /home/mart_i/Work/unix/Zappy/lists/wrapper/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Tue Jun 12 13:24:35 2012 pierre martin
** Last update Tue Jun 12 16:54:08 2012 pierre martin
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
