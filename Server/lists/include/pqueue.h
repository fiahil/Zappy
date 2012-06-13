/*
** pqueue.h for c_lists in /home/mart_i/Work/unix/Zappy/lists/include/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on  Tue Jun 12 10:33:39 2012 pierre martin
** Last update Tue Jun 12 11:06:35 2012 pierre martin
*/

#ifndef __PQUEUE_H__
#define __PQUEUE_H__

#include	"c_lists.h"

typedef struct	s_pqueue
{
  t_cmp		cmp;
  t_list	queue;
}		t_pqueue;

t_pqueue	*new_pqueue(t_cmp cmp);
void		init_pqueue(t_pqueue *this, t_cmp cmp);
void		pqueue_push(t_pqueue *this, void *data, size_t len);
void		*pqueue_next(t_pqueue *this);
void		pqueue_pop(t_pqueue *this);

#endif /* __PQUEUE_H__ */

