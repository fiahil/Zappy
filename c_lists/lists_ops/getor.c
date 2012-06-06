/*
** getor.c for c_lists in /home/mart_i/Work/unix/irc-mart_i-magere_n/c_lists/lists_ops/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Thu Apr 19 00:35:24 2012 pierre martin
** Last update Thu Apr 19 00:41:17 2012 pierre martin
*/

#include	"iter.h"
#include	"c_lists.h"

void		*get_content(t_iter *it)
{
  if (it)
    return (it->data);
  return (NULL);
}

void		*list_front(t_list *this)
{
  if (this && this->head)
    return (this->head->data);
  return (NULL);
}

void		*list_back(t_list *this)
{
  if (this && this->tail)
    return (this->tail->next);
  return (NULL);
}

t_iter		*list_begin(t_list *this)
{
  if (this)
    return (this->head);
  return (NULL);
}

t_iter		*list_end(t_list *this)
{
  if (this)
    return (this->tail);
  return (NULL);
}
