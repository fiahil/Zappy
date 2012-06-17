
#include	"iter.h"
#include	"c_lists.h"

void		list_push_back_ctor(t_list *this, ...)
{
  va_list	param;

  if (this)
    {
      va_start(param, this);
      list_push_back(this, new_iter_ctor(this->ctor, param));
      va_end(param);
    }
}

void		list_push_front_ctor(t_list *this, ...)
{
  va_list	param;

  if (this)
    {
      va_start(param, this);
      list_push_front(this, new_iter_ctor(this->ctor, param));
      va_end(param);
    }
}

void		list_insert_ctor(t_list *this, t_iter *pos, ...)
{
  va_list	param;

  if (this)
    {
      va_start(param, pos);
      list_insert(this, pos, new_iter_ctor(this->ctor, param));
      va_end(param);
    }
}
