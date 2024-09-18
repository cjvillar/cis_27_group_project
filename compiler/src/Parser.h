#pragma once

#include "config.h"

class Parser {
 public:
  Parser(const std::string& input);

  void parse();
  std::unique_ptr<ExprAST>& getResult();

 private:
  Lexer lexer;
  std::stack<Token> operatorStack;
  std::vector<std::unique_ptr<ExprAST>> partialParse;
  std::unique_ptr<ExprAST> result;
};
