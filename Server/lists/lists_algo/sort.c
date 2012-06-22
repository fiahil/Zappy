
#include	"c_lists.h"
#include	"algorithm.h"

static t_iter	*get_head(t_list *this)
{
  t_iter	*e;

  e = this->head;
  this->head = e->next;
  if (this->head)
    this->head->prev = NULL;
  --this->size;
  this->empty = this->size ? 1 : 0;
  return (e);
}

static void	split(t_list *l1, t_list *l2, t_cmp cmp)
{
  t_iter	*e1;
  t_iter	*e2;

  if (l1 && l1->size > 1)
    {
      e1 = get_head(l1);
      e2 = get_head(l1);
      split(l1, l2, cmp);
      list_push_front(l1, e1);
      list_push_front(l2, e2);
    }
}

static void	merge(t_list *l1, t_list *l2, t_cmp cmp)
{
  t_iter	*it;

  if (l1->size == 0)
    list_swap(l1, l2);
  else if (l2->size != 0)
    {
      if (cmp(l1->head->data, l1->head->len,
	      l2->head->data, l2->head->len) <= 0)
	it = get_head(l1);
      else
	it = get_head(l2);
      merge(l1, l2, cmp);
      list_push_front(l1, it);
    }
}

void	list_sort(t_list *this, t_cmp cmp)
{
  t_list	tmp;

  if (this && this->size > 1)
    {
      init_list(&tmp, NULL, NULL, NULL);
      split(this, &tmp, cmp);
      list_sort(this, cmp);
      list_sort(&tmp, cmp);
      merge(this, &tmp, cmp);
    }
}
