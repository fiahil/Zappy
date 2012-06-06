/*
** add_new.c for c_lists in /home/mart_i/Work/unix/irc-mart_i-magere_n/c_lists/lists_ops/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Wed Apr 18 00:00:25 2012 pierre martin
** Last update Wed Apr 18 15:06:08 2012 pierre martin
*/

#include	"iter.h"
#include	"c_lists.h"

void		list_push_back_new(t_list *this, void *param, size_t len)
{
  if (this)
    list_push_back(this, new_iter_param(param, len));
}

void		list_push_front_new(t_list *this, void *param, size_t len)
{
  if (this)
    list_push_front(this, new_iter_param(param, len));
}

void		list_insert_new(t_list *this, t_iter *pos, void *param, size_t len)
{
  if (this)
    list_insert(this, pos, new_iter_param(param, len));
}
