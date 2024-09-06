%{
#include <stdio.h>

enum Tokens {
    BORK = 1,
    ADD,
    SUB,
    MUL,
    DIV,
    NUMBER,
    STRING
};
%}

/* Definitions */
%%
bork                { return BORK; }       /* "bork" token for print */
"+"                 { return ADD; }        /* Addition */
"-"                 { return SUB; }        /* Subtraction */
"*"                 { return MUL; }        /* Multiplication */
"/"                 { return DIV; }        /* Division */
[0-9]+              { return NUMBER; }     /* Numbers */
\"[^\"]*\"          { return STRING; }     /* Strings */
[ \t\n]+            ;                      /* Ignore whitespace */
.                   { printf("Unexpected character: %s\n", yytext); } /* Catch-all for errors */
%%

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    yylex();
    return 0;
}

