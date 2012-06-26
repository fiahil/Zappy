/*
** features.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:24:07 2012 ulric lefevre
** Last update Sat Jun 23 20:24:08 2012 ulric lefevre
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
