#include "config.h"

Parser::Parser(const std::string& input) : lexer(input) {}

void Parser::parse() {
  // Shunting-yard algorithm for fully parenthesized
  // arithmetic expressions
  Token token;
  while ((token = lexer.getNextToken()).getKind() != TokenKind::END) {
    switch (token.getKind()) {
      // Build NumExpr out of any numeric token and push it
      // onto the list of partially parsed expressions.
      case TokenKind::NUMBER: {
        std::unique_ptr<ExprAST> numExpr = std::make_unique<NumExprAST>(token);
        partialParse.push_back(std::move(numExpr));
        break;
      }
      // Only pop operators and build new BinOp nodes when you
      // encounter a right parenthesis.
      case TokenKind::RPAREN:
        if (operatorStack.size() < 2 || partialParse.size() < 2) {
          // Error: too few operators on stack
          throw std::runtime_error("Syntax error: too few operators.");
        } else {
          std::unique_ptr<ExprAST> binOpExpr = std::make_unique<BinOpExprAST>(
              operatorStack.top(), partialParse[partialParse.size() - 2],
              partialParse[partialParse.size() - 1]);
          operatorStack.pop();
          // After popping operator, check if there is a preceding
          // left parenthesis.
          if (operatorStack.top().getKind() != TokenKind::LPAREN) {
            // Error: all BinOp expressions must be parenthesized
            throw std::runtime_error("Syntax error: unbalanced parentheses.");
          } else {
            operatorStack.pop();
            partialParse.pop_back();
            partialParse.pop_back();
            partialParse.push_back(std::move(binOpExpr));
          }
        }
        break;
      // All other operators get pushed onto the stack
      default:
        operatorStack.push(token);
        break;
    }
  }
  if (partialParse.size() != 1) {
    throw std::runtime_error("Syntax error. Parse failed.");
  } else {
    result = std::move(partialParse[0]);
  }
}

std::unique_ptr<ExprAST>& Parser::getResult() { return result; }
