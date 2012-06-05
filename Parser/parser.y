/*
 * Fiahil
 *
 * 8 Mai 2012
 */

%parse-param { int number }

%{
#include <stdio.h>

#define YYSTYPE char const*

  int	yylex(void);
  void	yyerror(int, char const *);
%}

%token PLOP END EOL

%%

input:
/* empty */
| PLOP	{ puts("I GET A PLOP!"); }
| END	{ puts("I GET AN END!"); }
| EOL

%%

void	yyerror(int n, char const *s) {
  fprintf(stderr, "%d - %s\n", n, s);
}
