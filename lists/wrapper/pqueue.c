/*
** pqueue.c for c_lists in /home/mart_i/Work/unix/Zappy/lists/wrapper/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Tue Jun 12 10:31:25 2012 pierre martin
** Last update Tue Jun 12 11:50:50 2012 pierre martin
*/

#include	<assert.h>
#include	<stdlib.h>

#include	"pqueue.h"

t_pqueue	*new_pqueue(t_cmp cmp)
{
  t_pqueue	*this;

  assert(cmp != NULL);
  this = malloc(sizeof(t_pqueue));
  if (this)
    init_pqueue(this, cmp);
  return this;
}

void		init_pqueue(t_pqueue *this, t_cmp cmp)
{
  if (this)
    {
      this->cmp = cmp;
      init_list(&(this->queue), NULL, NULL, NULL);
    }
}

void		pqueue_push(t_pqueue *this, void *data, size_t len)
{
  t_iter	*it;

  it = list_begin(&(this->queue));
  while (it && this->cmp(data, len, it->data, it->len) > 0)
    it = it->next;
  list_insert_new(&(this->queue), it, data, len);
}

void		*pqueue_next(t_pqueue *this)
{
  return (this->queue.head->data);
}

void		pqueue_pop(t_pqueue *this)
{
  list_pop_front(&(this->queue));
}
