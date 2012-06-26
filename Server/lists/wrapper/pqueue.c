/*
** pqueue.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:23:56 2012 ulric lefevre
** Last update Sat Jun 23 20:23:57 2012 ulric lefevre
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
