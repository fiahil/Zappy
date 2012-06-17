
#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

void	list_sort(t_list *this, t_cmp cmp);
t_iter	*list_find(t_list *this, void *param);
t_iter	*list_find_if(t_list *this, t_predicate p);
t_iter	*list_find_cmp(t_list *this, t_cmp p, void *ref, size_t reflen);
void	list_for_each(t_list *this, t_func f);
size_t	list_count(t_list *this, void *value);
size_t	list_count_if(t_list *this, t_predicate p);
void	list_reverse(t_list* this);
void	list_swap(t_list* this, t_list* lst);

#endif /* __ALGORITHM_H__ */

