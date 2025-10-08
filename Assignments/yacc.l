%{
#include <stdio.h>
#include <ctype.h>

int yylex(void);
int yyerror(const char *s);
%}

%union { double dval; }

%token <dval> NUMBER
%type  <dval> expr

%left '+' '-'
%left '*' '/'
%right UMINUS

%%
lines:
    | lines expr '\n' { printf("= %g\n", $2); }
    | lines '\n'
    ;

expr:
      expr '+' expr   { $$ = $1 + $3; }
    | expr '-' expr   { $$ = $1 - $3; }
    | expr '*' expr   { $$ = $1 * $3; }
    | expr '/' expr   { $$ = $1 / $3; }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | '(' expr ')'    { $$ = $2; }
    | NUMBER          { $$ = $1; }
    ;
%%

int yylex(void) {
    int c;
    while (isspace(c = getchar()));
    if (isdigit(c) || c == '.') {
        ungetc(c, stdin);
        scanf("%lf", &yylval.dval);
        return NUMBER;
    }
    return c;
}
int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}
int main(void) {
    puts("Enter expressions (Ctrl+D to exit):");
    return yyparse();
}
