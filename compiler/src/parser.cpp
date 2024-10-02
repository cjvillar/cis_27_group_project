#include "config.h"

Parser::Parser(const std::string& input) : lexer(input) {}

void Parser::parse() {
  Token token;
  while ((token = lexer.getNextToken()).getKind() != TokenKind::END) {
    switch (token.getKind()) {
      case TokenKind::NUMBER:
        handleNumber(token);
        break;
      case TokenKind::RPAREN:
        handleRightParenthesis();
        break;
      default:
        handleOperator(token);
        break;
    }
  }
  validateResult();
}

void Parser::handleNumber(const Token& token) {
  std::unique_ptr<ExprAST> numExpr = std::make_unique<NumExprAST>(token);
  partialParse.push_back(std::move(numExpr));
}

void Parser::handleOperator(const Token& token) { operatorStack.push(token); }

void Parser::handleRightParenthesis() {
  if (operatorStack.size() < 2 || partialParse.size() < 2) {
    throw std::runtime_error("Syntax error: too few operators.");
  }

  std::unique_ptr<ExprAST> binOpExpr = std::make_unique<BinOpExprAST>(
      operatorStack.top(), partialParse[partialParse.size() - 2],
      partialParse[partialParse.size() - 1]);
  operatorStack.pop();

  if (operatorStack.top().getKind() != TokenKind::LPAREN) {
    throw std::runtime_error("Syntax error: unbalanced parentheses.");
  }
  operatorStack.pop();

  partialParse.pop_back();
  partialParse.pop_back();
  partialParse.push_back(std::move(binOpExpr));
}

void Parser::validateResult() {
  if (partialParse.size() != 1) {
    throw std::runtime_error("Syntax error. Parse failed.");
  }
  result = std::move(partialParse[0]);
}

std::unique_ptr<ExprAST>& Parser::getResult() { return result; }