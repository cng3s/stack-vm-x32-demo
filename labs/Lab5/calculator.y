
%{
  #include <stdio.h>
  #include <stdlib.h>
  void yyerror(char *s);
  int  yylex();
%}

%left '+' '-'


%%

lines: line
     | line lines
;

line: exp '\n';

exp: '('exp')'
   | exp '+' term
   | exp '-' term
   | term
;

term: term '*' nums
    | term '/' nums
    | nums
;

nums: n
    | n nums
;

n: '1'|'2'|'3'|'4'|'5'|'6'|'7'|'8'|'9'|'0';


%%

int yylex()
{
  return getchar();
}

void yyerror (char *s)
{
  fprintf(stderr, "%s\n", s);
  return;
}

int main(int argc, char **argv)
{
  yyparse();
  return 0;
}
