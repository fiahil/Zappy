
#include	"iter.h"
#include	"c_lists.h"

void		list_push_back_new(t_list *this, void *param, size_t len)
{
  if (this)
    list_push_back(this, new_iter_param(param, len));
}

void		list_push_front_new(t_list *this, void *param, size_t len)
{
  if (this)
    list_push_front(this, new_iter_param(param, len));
}

void		list_insert_new(t_list *this, t_iter *pos, void *param, size_t len)
{
  if (this)
    list_insert(this, pos, new_iter_param(param, len));
}
