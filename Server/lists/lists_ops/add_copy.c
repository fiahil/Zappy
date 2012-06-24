/*
** add_copy.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:25:04 2012 ulric lefevre
** Last update Sat Jun 23 20:25:04 2012 ulric lefevre
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
