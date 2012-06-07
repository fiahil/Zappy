/*
** remove.c for c_lists in /home/mart_i/Work/unix/irc-mart_i-magere_n/c_lists/lists_ops/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Wed Apr 18 11:27:56 2012 pierre martin
** Last update Thu Jun  7 17:47:45 2012 pierre martin
*/

#include	"iter.h"
#include	"c_lists.h"

void		list_pop_back(t_list *this)
{
  t_iter	*del;

  if (this && this->size)
    {
      del = this->tail;
      if (this->tail->prev)
	this->tail->prev->next = NULL;
      this->tail = this->tail->prev;
      if (this->head == del)
	this->head = this->tail;
      delete_iter(del, this->dtor);
      --this->size;
      this->empty = this->size ? 0 : 1;
    }
}

void		list_pop_front(t_list *this)
{
  t_iter	*del;

  if (this && this->size)
    {
      del = this->head;
      if (this->head->next)
	this->head->next->prev = NULL;
      this->head = this->head->next;
      if (this->tail == del)
	this->tail = this->head;
      delete_iter(del, this->dtor);
      --this->size;
      this->empty = this->size ? 0 : 1;
    }
}

static t_iter	*extract(t_iter *it)
{
  t_iter	*e;

  e = it->next;
  it->next = e->next;
  if (e->next)
    e->next->prev = it;
  return (e);
}

void		list_remove(t_list *this, void *param)
{
  t_iter	*it;

  if (this)
    {
      while (this->size && this->head->data == param)
	list_pop_front(this);
      it = this->head;
      while (it && it->next)
	{
	  if (it->next->data == param)
	    delete_iter(extract(it), this->dtor);
	  else if (it)
	    it = it->next;
	}
    }
}

void		list_remove_if(t_list *this, t_predicate pred)
{
  t_iter	*it;

  if (this)
    {
      while (this->size && pred(this->head->data, this->head->len))
	list_pop_front(this);
      it = this->head;
      while (it && it->next)
	{
	  if (pred(it->next->data, it->next->len))
	    delete_iter(extract(it), this->dtor);
	  else if (it)
	    it = it->next;
	}
    }
}
