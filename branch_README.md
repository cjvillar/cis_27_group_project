## Lexer -> Tokens:

Lexer.cpp: A lexer class to tokenize the following
Operators: + , - , \* , /
Expressions: Numbers ([0-9.]+), Parentheses
Keywords: None (Currently)

test Lexer:

```bash
clang++ -std=c++17 -o lexer_test test_lexer.cpp
```

test both Lexer and Parser:

```bash
clang++ -std=c++17 -o parser_test parser_test.cpp Parser.cpp Lexer.cpp
```

### sources:

Most of the driver code is cobbled together from these two sources, with some modifications:

https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl02.html
https://github.com/PacktPublishing/Learn-LLVM-17/tree/main/Chapter02

## Tokens -> ASTs:

parser.cpp implements the Shunting-Yard Algorithm to recognize fully
parenthesized arithmetic expressions. It cannot handle operator
precedence (yet).

ASTs come in two concrete forms: `NumExprAST`, mostly just a wrapper for numeric values,
and `BinOpExprAST`, which contains a data member for type of operator (PLUS, MINUS, MULTIPLY, DIVIDE)
and pointers to two child nodes of abstract type `ExprAST`.

`parser_test.cpp` contains a few sample strings. The first two should succeed and pretty-print
and AST to console, and the last should fail.

Please note that ASTs are printed with the method `print("")`, which requires the empty string
argument to format correctly. This is because it is called recursively with increasing indent levels
for the children of `BinOpExpr` nodes. It is separate from `operator<<` because I haven't yet figured out
how to get the overrides for the concrete child classes to work when called on the abstract parent class
`ExprAST`.

test:

```bash
clang++ -std=c++17 -o parser_test parser_test.cpp
```

## Compiler
In its current state, we have main.cpp as the driver for the compilation phase. It takes one argument string on invocation and prints LLVM
IR to stdout, evaluating arithmetic expressions to a single value and outputting the basic block for @main, which has a call to @write. 

Example usage:

```bash
/cis_27_group_project/compiler/src$ cmake -S. -B ../build
/cis_27_group_project/compiler/build$ make
```

```bash
./Compiler "(5 + (10 * 7))"
```

Now from src run
```bash
./../build/Compiler infile.txt 
```

output:

```
; ModuleID = 'arithmetic'
source_filename = "arithmetic"

define i32 @main(i32 %0) {
entry:
  call void @write_fn(i32 75)
  ret i32 0
}

declare void @write_fn(i32)
```

Note: I don't fully understand the `run` method of class `IRGenVisitor` yet. It comes pretty much verbatim from "Learn LLVM 17" so I'll have to read more to understand how to modify it. 