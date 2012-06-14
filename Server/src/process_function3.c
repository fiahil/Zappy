/*
 * Fiahil
 * 06.06.2012
 */

#include <stdlib.h>
#include <string.h>
#include "process_function.h"

t_bool  move_process_function(t_clientManager this, char *data)
{
  (void)data;
  list_push_back_new(this->out, "I move !\n", strlen("I move !\n") + 1);
  return (TRUE);
}

t_bool  right_process_function(t_clientManager this, char *data)
{
  (void)data;
  list_push_back_new(this->out, "I turn right !\n", strlen("I turn right !\n") + 1);
  return (TRUE);
}

t_bool  left_process_function(t_clientManager this, char *data)
{
  (void)data;
  list_push_back_new(this->out, "I turn left !\n", strlen("I turn left !\n") + 1);
  return (TRUE);
}

