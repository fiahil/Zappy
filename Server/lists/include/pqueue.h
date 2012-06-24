/*
** pqueue.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:24:50 2012 ulric lefevre
** Last update Sat Jun 23 20:24:51 2012 ulric lefevre
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
void		delete_pqueue(t_pqueue *this);

#endif /* __PQUEUE_H__ */

