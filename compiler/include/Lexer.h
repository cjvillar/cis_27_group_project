#ifndef LEXER_H
#define LEXER_H

#include "config.h"

class Lexer {
 public:
  Lexer(std::string_view input);

  std::vector<ReservedToken> tokenize();
  std::vector<std::string> getTokenValues() const;

 private:
  std::string_view input;
  size_t position;
  std::vector<int> numbers;
  std::vector<std::string> tokenValues;

  std::string readKeyword();
  int readNumber();
  ReservedToken findKeyword(const std::string& keyword) const;
  ReservedToken findOperator(const std::string& op) const;
};

#endif // LEXER_H
