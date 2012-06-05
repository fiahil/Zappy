/*
 * Fiahil
 *
 * 3 Mai 2012
 */

%option header-file="lex.yy.h"
%option noyywrap nounput noinput

%{
#include <stdio.h>
#include "parser.tab.h"
%}

%%

plop	{
  puts("THIS IZ PLOP!");
  return PLOP;
}

end	{
  puts("THIS IZ END!");
  return END;
}

'\n'	{
  return EOL;
}

%%

