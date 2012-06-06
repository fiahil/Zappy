/*
** iter.c for c_lists in /home/mart_i/Work/unix/irc-mart_i-magere_n/c_lists/
** 
** Made by pierre martin
** Login   <mart_i@epitech.net>
** 
** Started on Tue Apr 17 13:32:25 2012 pierre martin
** Last update Wed Apr 18 23:18:02 2012 pierre martin
*/

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
