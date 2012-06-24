/*
** item.h for zappy_bibicy in /home/lefevr_u/GIT/zappy/Zappy/Server
** 
** Made by ulric lefevre
** Login   <lefevr_u@epitech.net>
** 
** Started on  Sat Jun 23 20:24:27 2012 ulric lefevre
** Last update Sat Jun 23 20:24:36 2012 ulric lefevre
*/

#ifndef __ITEM_H__
#define __ITEM_H__

#include	<unistd.h>

/*
**   Definition of item structure for chained-lists
*/
typedef struct s_item
{
  void		*data;
  size_t	len;
  struct s_item	*next;
  struct s_item	*prev;
}		t_item;

/*
**   Prototype of function to deal with chained-lists' item
**
**   Allocators for chained-lists' item
*/
t_item		*new_item();
t_item		*new_item_param(void *, size_t);
t_item		*new_item_copy(t_item *);

/*
**   Initialazers for chained-lists' item
*/
t_item		*init_item_def();
t_item		*init_item_param(t_item *, void *, size_t);
t_item		*init_item_copy(t_item *);

/*
**   Desallocator for chained-lists' item
*/
void		delete_item(t_item *);
void		delete_items(t_item *);

#endif /* __ITEM_H__ */

