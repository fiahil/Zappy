/*
 * Fiahil
 *
 * 3 Mai 2012
 */

%option header-file="lex.yy.h"
%option noyywrap nounput noinput

%{
#include <string.h>
#include <stdio.h>
#include "parser.tab.h"
%}

%%

[:print:]+	{
  yylval.str = strndup(yytext, yyleng);
  return WORD;
}

(linemate|deraumere|sibur|mendiane|phiras|thystame|nourriture)	{
  yylval.str = strndup(yytext, yyleng);
  return OBJECT;
}

"voir"		{
  return SEE;
}

"avance"	{
  return WALK;
}

"droite"	{
  return RIGHT;
}

"gauche"	{
  return LEFT;
}

"inventaire"	{
  return INVENTORY;
}

"prend"		{
  return TAKE;
}

"pose"		{
  return PUT;
}

"expulse"	{
  return KICK;
}

"broadcast"	{
  return BROADCAST;
}

"incantation"	{
  return INCANTATION;
}

"fork"		{
  return FORK;
}

"connect_nbr"	{
  return CONNECT;
}

%%

