/*
** c_lists.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:24:43 2012 ulric lefevre
** Last update Mon Jun 25 18:21:12 2012 pierre martin
*/

#ifndef __C_LISTS_H__
#define __C_LISTS_H__

#include	"iter.h"

/*
**   Definition of structure for chained-lists
*/
typedef struct s_list
{
  int		empty;
  size_t	size;
  t_ctor	ctor;
  t_dtor	dtor;
  t_copy	copy;
  t_iter	*head;
  t_iter	*tail;
}		t_list;

typedef int	(*t_cmp)(void *, size_t, void *, size_t);
typedef int	(*t_predicate)(void *, size_t);
typedef void	(*t_func)(void *, size_t);

/*
**   Prototypes of function to deal with chained-lists
**
**   Allocators for chained-lists
*/
t_list		*init_list(t_list *, t_ctor, t_dtor, t_copy);
t_list		*new_list(t_ctor, t_dtor, t_copy);

/*
**   Functions to add elements
*/
void		list_push_back(t_list *this, t_iter *add);
void		list_push_front(t_list *this, t_iter *add);
void		list_insert(t_list *this, t_iter *pos, t_iter *add);

void		list_push_back_new(t_list *this, void *param, size_t len);
void		list_push_front_new(t_list *this, void *param, size_t len);
void		list_insert_new(t_list *this, t_iter *pos, void *p, size_t l);

void		list_push_back_ctor(t_list *this, ...);
void		list_push_front_ctor(t_list *this, ...);
void		list_insert_ctor(t_list *this, t_iter *pos, ...);

void		list_push_back_copy(t_list *this, t_iter *add);
void		list_push_front_copy(t_list *this, t_iter *add);
void		list_insert_copy(t_list *this, t_iter *pos, t_iter *add);

/*
**   Functions to remove elements
*/
void		list_pop_back(t_list *this);
void		list_pop_front(t_list *this);
void		list_remove(t_list *this, void *param);
void		list_remove_if(t_list *this, t_predicate pred);
t_iter		*list_extract(t_list *this, t_iter *it);

/*
**   Functions to get elements
*/
void		*list_front(t_list *this);
void		*list_back(t_list *this);
void		*get_content(t_iter *it);
t_iter		*list_begin(t_list *this);
t_iter		*list_end(t_list *this);

/*
**   Desallocator for chained-lists
*/
void		list_clear(t_list *this);
void		delete_list(t_list *this);

#endif /* __C_LISTS_H__ */
