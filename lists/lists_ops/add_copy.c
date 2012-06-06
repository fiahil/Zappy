/*
** add_copy.c for c_lists in /home/mart_i/Work/unix/irc-mart_i-magere_n/c_lists/lists_ops/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Wed Apr 18 00:07:14 2012 pierre martin
** Last update Wed Apr 18 23:27:42 2012 pierre martin
*/

#include	"iter.h"
#include	"c_lists.h"

void		list_push_back_copy(t_list *this, t_iter *add)
{
  if (this)
    list_push_back(this, new_iter_copy(add, this->copy));
}

void		list_push_front_copy(t_list *this, t_iter *add)
{
  if (this)
    list_push_front(this, new_iter_copy(add, this->copy));
}

void		list_insert_copy(t_list *this, t_iter *pos, t_iter *add)
{
  if (this)
    list_insert(this, pos, new_iter_copy(add, this->copy));
}
