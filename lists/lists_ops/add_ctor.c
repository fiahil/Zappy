/*
** add_ctor.c for c_lists in /home/mart_i/Work/unix/irc-mart_i-magere_n/c_lists/lists_ops/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Wed Apr 18 23:45:58 2012 pierre martin
** Last update Thu Apr 19 00:03:39 2012 pierre martin
*/

#include	"iter.h"
#include	"c_lists.h"

void		list_push_back_ctor(t_list *this, ...)
{
  va_list	param;

  if (this)
    {
      va_start(param, this);
      list_push_back(this, new_iter_ctor(this->ctor, param));
      va_end(param);
    }
}

void		list_push_front_ctor(t_list *this, ...)
{
  va_list	param;

  if (this)
    {
      va_start(param, this);
      list_push_front(this, new_iter_ctor(this->ctor, param));
      va_end(param);
    }
}

void		list_insert_ctor(t_list *this, t_iter *pos, ...)
{
  va_list	param;

  if (this)
    {
      va_start(param, pos);
      list_insert(this, pos, new_iter_ctor(this->ctor, param));
      va_end(param);
    }
}
