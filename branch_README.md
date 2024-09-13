## Lexer -> Tokens:

Lexer.cpp: A lexer class to tokenize the following
Operators: + , - , * , /
Expressions: Numbers ([0-9.]+), Parentheses
Keywords: None (Currently)

test:
```bash
clang++ -std=c++17 -o lexer_test test_lexer.cpp
```

### sources:
https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl02.html

## Tokens -> ASTs:

parser.cpp implements the Shunting-Yard Algorithm to recognize fully
parenthesized arithmetic expressions. It cannot handle operator 
precedence (yet). 

ASTs come in two concrete forms: `NumExprAST`, mostly just a wrapper for numeric values,
and `BinOpExprAST`, which contains a data member for type of operator (PLUS, MINUS, MULTIPLY, DIVIDE)
and pointers to two child nodes of abstract type `ExprAST`. 

`parser_test.cpp` contains a few sample strings. The first two should succeed and pretty-print
and AST to console, and the last should fail. 

test:
```bash
clang++ -std=c++17 -o parser_test parser_test.cpp
```