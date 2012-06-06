/*
** algo_st.c for c_lists in /home/mart_i/Work/unix/irc-mart_i-magere_n/c_lists/lists_ops/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Thu Apr 19 00:25:46 2012 pierre martin
** Last update Wed Jun  6 11:55:16 2012 pierre martin
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

void		list_for_each(t_list *this, t_func f)
{
  t_iter	*it;

  if (this)
    {
      it = this->head;
      while (it)
	{
	  f(it->data, it->len);
	  it = it->next;
	}
    }
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
