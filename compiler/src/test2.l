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
bork                { printf("BORK token\n"); return BORK; }   /* "bork" token for print */
"+"                 { printf("ADD token\n"); return ADD; }     /* Addition */
"-"                 { printf("SUB token\n"); return SUB; }     /* Subtraction */
"*"                 { printf("MUL token\n"); return MUL; }     /* Multiplication */
"/"                 { printf("DIV token\n"); return DIV; }     /* Division */
[0-9]+              { printf("NUMBER token: %s\n", yytext); return NUMBER; }  /* Numbers */
\"[^\"]*\"          { printf("STRING token: %s\n", yytext); return STRING; }  /* Strings */
[ \t\n]+            ;  /* Ignore whitespace */
.                   { printf("Unexpected character: %s\n", yytext); }  /* Catch-all for errors */
%%

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    yylex();
    return 0;
}
