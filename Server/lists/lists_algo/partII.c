/*
** partII.c for zappy_bibicy* in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:24:10 2012 ulric lefevre
** Last update Sat Jun 23 20:24:12 2012 ulric lefevre
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
