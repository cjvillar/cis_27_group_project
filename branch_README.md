## Lexer -> Tokens:

Lexer.cpp: A lexer class to tokenize the following
Operators: + , - , * , /
Expressions: Numbers ([0-9.]+), Parentheses
Keywords: None (Currently)

test:
```bash
clang++ -std=c++17 -o test main.cpp
```

Output:
```bash

Token(Type: NUMBER, Value: 12)
Token(Type: PLUS, Value: )
Token(Type: NUMBER, Value: 24)
Token(Type: MINUS, Value: )
Token(Type: LPAREN, Value: )
Token(Type: NUMBER, Value: 3)
Token(Type: MULTIPLY, Value: )
Token(Type: NUMBER, Value: 4)
Token(Type: RPAREN, Value: )
Token(Type: DIVIDE, Value: )
Token(Type: NUMBER, Value: 6)

```



### sources:
https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl02.html