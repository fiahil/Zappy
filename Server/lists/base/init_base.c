
#include	<string.h>
#include	<stdlib.h>
#include	"iter.h"

t_iter		*init_iter_def(t_iter *this)
{
  if (this)
    {
      this->data = NULL;
      this->len = 0;
      this->next = NULL;
      this->prev = NULL;
    }
  return (this);
}

t_iter		*init_iter_woa(t_iter *this, void *param)
{
  if (this)
    this->data = param;
  return (this);
}

t_iter		*init_iter_param(t_iter *this, void *param, size_t len)
{
  if (this)
    {
      if (param && len)
	{
	  this->data = malloc(len);
	  if (this->data)
	    {
	      this->data = memcpy(this->data, param, len);
	      this->len = len;
	    }
	}
    }
  return (this);
}
