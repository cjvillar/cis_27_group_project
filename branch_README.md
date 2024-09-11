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