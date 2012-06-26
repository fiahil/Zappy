/*
** alloc_base.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:24:22 2012 ulric lefevre
** Last update Sat Jun 23 20:24:23 2012 ulric lefevre
*/

#include	<stdlib.h>

#include	"iter.h"

t_iter		*new_iter()
{
  return (init_iter_def(malloc(sizeof(t_iter))));
}

t_iter		*new_iter_ctor(t_ctor ctor, va_list param)
{
  if (ctor)
    return (init_iter_woa(new_iter(), ctor(param)));
  return (new_iter());
}

t_iter		*new_iter_param(void *param, size_t len)
{
  return (init_iter_param(new_iter(), param, len));
}

t_iter		*new_iter_copy(t_iter *from, t_copy copy)
{
  if (!from)
    return (NULL);
  if (copy)
    return (init_iter_woa(new_iter(), copy(from->data)));
  return (new_iter_param(from->data, from->len));
}
