// used only to test the output of the lexer.
//  Will not include if any merge to main

#include <iostream>

#include "Lexer.cpp"

std::string tokenTypeToString(TokenType type) {
  switch (type) {
    case TokenType::NUMBER:
      return "NUMBER";
    case TokenType::PLUS:
      return "PLUS";
    case TokenType::MINUS:
      return "MINUS";
    case TokenType::MULTIPLY:
      return "MULTIPLY";
    case TokenType::DIVIDE:
      return "DIVIDE";
    case TokenType::LPAREN:
      return "LPAREN";
    case TokenType::RPAREN:
      return "RPAREN";
    case TokenType::END:
      return "END";
    case TokenType::INVALID:
      return "INVALID";
    default:
      return "UNKNOWN";
  }
}

int main() {
  Lexer lexer("12 + 24 - (3 * 4) / 06");
  Token token = lexer.getNextToken();
  while (token.getType() != TokenType::END) {
    std::cout << "Token(Type: " << tokenTypeToString(token.getType())
              << ", Value: " << token.getValue() << ")\n";
    token = lexer.getNextToken();
  }
  return 0;
}