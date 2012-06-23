/*
** iter.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:24:47 2012 ulric lefevre
** Last update Sat Jun 23 20:24:47 2012 ulric lefevre
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
