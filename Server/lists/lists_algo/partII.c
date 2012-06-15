/*
** partII.c for c_lists in /home/mart_i/Work/unix/myirc-2015-2014s-magere_n/c_lists/lists_algo/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Thu May 31 22:20:27 2012 pierre martin
** Last update Fri Jun 15 11:12:05 2012 pierre martin
*/

#include	"iter.h"
#include	"c_lists.h"

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
