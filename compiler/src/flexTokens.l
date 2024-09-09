%{
#include "Parser.hpp"   // Bison header
#include <iostream>     // Include std::cerr for error output
#include <FlexLexer.h>  // Flex header for C++
%}

%%

[0-9]+[0-9]*               { yylval.num = atoi(yytext); return NUMBER; }
[ \t\n]+              ;  // Skip whitespace
"+"                   { return PLUS; }
"-"                   { return MINUS; }
"*"                   { return MULTIPLY; }
"/"                   { return DIVIDE; }
"("                   { return LPAREN; }
")"                   { return RPAREN; }

%%

int yywrap() {
    return 1; //end of input
}
