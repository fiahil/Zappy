
#include	<stdlib.h>

#include	"iter.h"

void		delete_iter(t_iter *this, t_dtor dtor)
{
  if (this)
    {
      if (this->data && dtor)
	dtor(this->data);
      else if (this->data)
	free(this->data);
      free(this);
    }
}

void		delete_iters(t_iter *this, t_dtor dtor)
{
  if (this)
    {
      if (this->next)
	delete_iters(this->next, dtor);
      delete_iter(this, dtor);
    }
}
