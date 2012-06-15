/*
** c_lists.h for c_list in /home/magere_n/work/projets_tek2/irc/myirc-2015-2014s-magere_n
** 
** Made by nicolas magere
** Login   <magere_n@epitech.net>
** 
** Started on  Sun Apr 22 21:55:52 2012 nicolas magere
** Last update Fri Jun 15 14:28:54 2012 pierre martin
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
**   Algorithms for chained-lists
*/
t_iter		*list_find(t_list *this, void *param);
void		list_for_each(t_list *this, t_func f);

/* t_iter		*list_iter_find_if(t_list *this, t_predicate pred); */
/*
**   Desallocator for chained-lists
*/
void		delete_list(t_list *this);

#endif /* __C_LISTS_H__ */
