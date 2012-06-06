/*
 * Fiahil
 *
 * 8 Mai 2012
 */

%parse-param { int number }

%{
#include <stdio.h>

  int	yylex(void);
  void	yyerror(int, char const *);
%}

%union
{
  char*	str;
}

%token <str> WORD OBJECT SEE WALK RIGHT LEFT INVENTORY TAKE PUT KICK
%token <str> BROADCAST INCANTATION FORK CONNECT

%%

input:
/* empty */
| SEE			{ puts("see"); }
| WALK			{ puts("walk"); }
| RIGHT			{ puts("right"); }
| LEFT			{ puts("left"); }
| INVENTORY		{ puts("inventory"); }
| TAKE OBJECT		{ printf("take %s\n", $2); }
| PUT OBJECT		{ printf("put %s\n", $2); }
| KICK			{ puts("kick"); }
| BROADCAST WORD	{ printf("broadcast %s\n", $2); }
| INCANTATION		{ puts("incantation"); }
| FORK			{ puts("fork"); }
| CONNECT		{ puts("connect"); }

%%

void	yyerror(int n, char const *s) {
  fprintf(stderr, "%d - %s\n", n, s);
}
