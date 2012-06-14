/*
** iter.h for c_list in /home/magere_n/work/projets_tek2/irc/myirc-2015-2014s-magere_n
** 
** Made by nicolas magere
** Login   <magere_n@epitech.net>
** 
** Started on  Sun Apr 22 21:57:32 2012 nicolas magere
** Last update Sun Apr 22 21:58:06 2012 nicolas magere
*/

#ifndef __ITER_H__
#define __ITER_H__

#include	<stdarg.h>
#include	<unistd.h>

/*
**   Definition of iter structure for chained-lists
*/
typedef struct s_iter
{
  void		*data;
  size_t	len;
  struct s_iter	*next;
  struct s_iter	*prev;
}		t_iter;

typedef void*	(*t_ctor)(va_list);
typedef void	(*t_dtor)(void *);
typedef void*	(*t_copy)(void *);

/*
**   Prototype of function to deal with chained-lists' iter
**
**   Allocators for chained-lists' iter
*/
/* Create a default empty iterator */
t_iter		*new_iter();
/* Create an iterator for native type */
t_iter		*new_iter_param(void *, size_t);
/* Create an iterator for complex type*/
t_iter		*new_iter_ctor(t_ctor, va_list);
/* Copy an iterator for native or complex types if t_copy is set */
t_iter		*new_iter_copy(t_iter *, t_copy);

/*
**
**   Initialazers for chained-lists' iter
**
*/
t_iter		*init_iter_def(t_iter *);
t_iter		*init_iter_woa(t_iter *, void *);
t_iter		*init_iter_param(t_iter *, void *, size_t);

/*
**   Desallocator for chained-lists' iter
*/
void		delete_iter(t_iter *, t_dtor);
void		delete_iters(t_iter *, t_dtor);

#endif /* __ITER_H__ */
