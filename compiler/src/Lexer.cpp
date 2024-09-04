#include "config.h"

Lexer::Lexer(std::string_view input) : input(input), position(0) {}

std::vector<ReservedToken> Lexer::tokenize() {
  std::vector<ReservedToken> tokens;
  while (position < input.size()) {
    char currentChar = input[position];
    if (isspace(currentChar)) {
      ++position;
      continue;
    }
    if (std::isalpha(currentChar)) {
      auto keyword = readKeyword();
      ReservedToken token = findKeyword(keyword);
      tokens.push_back(token);
      tokenValues.push_back(keyword);  // Store the actual keyword value
      continue;
    }
    if (std::isdigit(currentChar)) {
      auto number = readNumber();
      tokens.push_back(ReservedToken::NUMBER);  // Add a token for numbers
      tokenValues.push_back(std::to_string(number));  // Store the number value
      continue;
    }
    if (std::string("+-*/=").find(currentChar) != std::string::npos) {
      auto token = findOperator(std::string(1, currentChar));
      tokens.push_back(token);
      tokenValues.push_back(std::string(1, currentChar));  // Store operator value
      ++position;
      continue;
    }
    throw std::runtime_error("Unexpected character: " + std::string(1, currentChar));
  }
  return tokens;
}

std::vector<std::string> Lexer::getTokenValues() const {
  return tokenValues;  // Return stored token values
}

std::string Lexer::readKeyword() {
  size_t start = position;
  while (position < input.size() && std::isalpha(input[position])) {
    ++position;
  }
  return std::string(input.substr(start, position - start));
}

int Lexer::readNumber() {
  size_t start = position;
  while (position < input.size() && std::isdigit(input[position])) {
    ++position;
  }
  return std::stoi(std::string(input.substr(start, position - start)));
}

ReservedToken Lexer::findKeyword(const std::string& keyword) const {
  if (keyword == "bork") return ReservedToken::BORK;

  // Handle unrecognized keywords
  throw std::runtime_error("Unrecognized keyword: " + keyword);
}

ReservedToken Lexer::findOperator(const std::string& op) const {
  if (op == "+") return ReservedToken::PLUS;
  if (op == "-") return ReservedToken::MINUS;
  if (op == "*") return ReservedToken::MULTIPLY;
  if (op == "/") return ReservedToken::DIVIDE;
  if (op == "=") return ReservedToken::EQUAL;

  // Handle unrecognized operators
  throw std::runtime_error("Unrecognized operator: " + op);
}



