/*
 * Fiahil
 * 05.06.2012
 */

#include <stdio.h>
#include "lex.yy.h"
#include "parser.tab.h"

int	yyparse(int);

int main(int ac, char **av)
{
  (void)ac;

  YY_BUFFER_STATE	buf = yy_scan_string(av[1]);
  yyparse(666);
  yy_delete_buffer(buf);
  return 0;
}
