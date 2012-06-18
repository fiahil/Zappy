
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
