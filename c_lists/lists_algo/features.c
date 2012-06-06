/*
** features.c for c_lists in /home/mart_i/Work/unix/myirc-2015-2014s-magere_n/c_lists/lists_algo/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Thu May 31 22:23:02 2012 pierre martin
** Last update Thu May 31 23:16:49 2012 pierre martin
*/

#include	"iter.h"
#include	"c_lists.h"

void	list_reverse(t_list* this)
{
  t_iter*	tmp;

  if (this)
    {
      this->tail = this->head;
      while (this->head->next)
	{
	  tmp = this->head->next;
	  this->head->next = this->head->prev;
	  this->head->prev = tmp;
	  this->head = tmp;
	}
      this->head->next = this->head->prev;
      this->head->prev = NULL;
    }
}

void	list_swap(t_list* this, t_list* lst)
{
  t_iter*	htmp;
  t_iter*	ttmp;
  size_t	stmp;
  int		etmp;

  htmp = this->head;
  ttmp = this->tail;
  stmp = this->size;
  etmp = this->empty;
  this->head = lst->head;
  this->tail = lst->tail;
  this->size = lst->size;
  this->empty = lst->empty;
  lst->head = htmp;
  lst->tail = ttmp;
  lst->size = stmp;
  lst->empty = etmp;
}

