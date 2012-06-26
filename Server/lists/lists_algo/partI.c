/*
** partI.c for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:23:59 2012 ulric lefevre
** Last update Sat Jun 23 20:24:00 2012 ulric lefevre
*/

#include	"iter.h"
#include	"c_lists.h"

t_iter		*list_find(t_list *this, void *param)
{
  t_iter	*it;

  if (this)
    {
      it = this->head;
      while (it)
	{
	  if (it->data == param)
	    return (it);
	  it = it->next;
	}
    }
  return (NULL);
}

t_iter		*list_find_if(t_list *this, t_predicate p)
{
  t_iter	*it;

  if (this)
    {
      it = this->head;
      while (it)
	{
	  if (!p(it->data, it->len))
	    return (it);
	  it = it->next;
	}
    }
  return (NULL);
}

t_iter		*list_find_cmp(t_list *this, t_cmp p, void *ref, size_t reflen)
{
  t_iter	*it;

  if (this)
    {
      it = this->head;
      while (it)
	{
	  if (!p(it->data, it->len, ref, reflen))
	    return (it);
	  it = it->next;
	}
    }
  return (NULL);
}

size_t		list_count(t_list *this, void *value)
{
  t_iter	*it;
  size_t	res;

  res = 0;
  if (this)
    {
      it = this->head;
      while (it)
	{
	  if (it->data == value)
	    ++res;
	  it = it->next;
	}
    }
  return  (res);
}

size_t		list_count_if(t_list *this, t_predicate p)
{
  t_iter	*it;
  size_t	res;

  res = 0;
  if (this)
    {
      it = this->head;
      while (it)
	{
	  if (!p(it->data, it->len))
	    ++res;
	  it = it->next;
	}
    }
  return  (res);
}
