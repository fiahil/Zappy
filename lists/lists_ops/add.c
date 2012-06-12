/*
** add.c for c_lists in /home/mart_i/Work/unix/irc-mart_i-magere_n/c_lists/include/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Tue Apr 17 23:26:13 2012 pierre martin
** Last update Tue Jun 12 11:45:36 2012 pierre martin
*/

#include	"c_lists.h"

void		list_push_back(t_list *this, t_iter *add)
{
  if (this && add)
    {
      add->prev = this->tail;
      if (!this->head)
	this->head = add;
      if (this->tail)
	this->tail->next = add;
      this->tail = add;
      add->next = NULL;
      ++this->size;
      this->empty = 0;
    }
}

void		list_push_front(t_list *this, t_iter *add)
{
  if (this && add)
    {
      add->next = this->head;
      if (!this->tail)
	this->tail = add;
      if (this->head)
	this->head->prev = add;
      this->head = add;
      add->prev = NULL;
      ++this->size;
      this->empty = 0;
    }
}

void		list_insert(t_list *this, t_iter *pos, t_iter *add)
{
  t_iter	*it;

  if (this && add)
    {
      if (this->head == pos)
	list_push_front(this, add);
      else
	{
	  it = this->head;
	  while (it && it->next != pos)
	      it = it->next;
	  if (it)
	    {
	      add->prev = it;
	      add->next = it->next;
	      if (it->next)
		it->next->prev = add;
	      it->next = add;
	      ++this->size;
	      this->empty = 0;
	    }
	}
    }
}
