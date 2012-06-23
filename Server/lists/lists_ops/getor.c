/*
** getor.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:25:17 2012 ulric lefevre
** Last update Sat Jun 23 20:25:17 2012 ulric lefevre
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
    return (this->tail->data);
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
  (void)this;
  return (NULL);
}
