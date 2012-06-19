
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

t_iter	*list_extract(t_list *this, t_iter *it)
{
  if (it)
    {
      if (it == this->head)
	this->head = it->next;
      if (it == this->tail)
	this->tail = it->prev;
      if (it->prev)
	it->prev->next = it->next;
      if (it->next)
	it->next->prev = it->prev;
      it->next = NULL;
      it->prev = NULL;
      --this->size;
      this->empty = this->size ? 0 : 1;
    }
  return (it);
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
	    delete_iter(list_extract(this, it->next), this->dtor);
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
	    delete_iter(list_extract(this, it->next), this->dtor);
	  else if (it)
	    it = it->next;
	}
    }
}
