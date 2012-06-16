
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
