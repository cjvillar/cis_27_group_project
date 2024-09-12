#pragma once

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <optional>


enum TokenKind {
    NUMBER, // 0 note to self* enums auto assign values
    PLUS, // 1 
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    END, // 7 (end of the input)
    INVALID // 8 (invalid or unrecognized token)
};

class Token {
  public:
    Token() : kind(INVALID), val(std::nullopt) {}
    Token(TokenKind kind) : kind(kind), val(std::nullopt) {}
    Token(TokenKind kind, std::optional<int> val) : kind(kind), val(val) {}
    TokenKind getKind() const { return kind; }
    std::optional<int> getValue() const { return val; }
  private:  
    TokenKind kind;
    std::optional<int> val;
};

// cout overrides for debugging
std::ostream& operator<<(std::ostream& os, std::optional<int> val) {
  if (val.has_value()) {
    std::cout << val.value();
  } else {
    std::cout << "no value";
  }
  return os;
}

class Lexer {
 public:
  Lexer(const std::string& text) // constructor 
      : text(text),
        pos(0), // tracks curent pos of string
        currentChar(text.empty() ? '\0' : text[0]), // the '0/' = null character, end of string
        numberValue(0) {} // stores number 

  Token getNextToken() { // returns next token
    while (currentChar != '\0') { 
      if (std::isspace(static_cast<unsigned char>(currentChar))) {
        skipWhitespace(); // skips white space
        continue;
      }

      if (std::isdigit(static_cast<unsigned char>(currentChar))) {
        numberValue = parseNumber();
        return Token(NUMBER, numberValue);
      }

      switch (currentChar) {
        case '+':
          advance();
          return Token(PLUS);
        case '-':
          advance();
          return Token(MINUS);
        case '*':
          advance();
          return Token(MULTIPLY);
        case '/':
          advance();
          return Token(DIVIDE);
        case '(':
          advance();
          return Token(LPAREN);
        case ')':
          advance();
          return Token(RPAREN);
        default:
          // handle invalid characters
          advance();  // skip invalid token but return invalid
          return Token(INVALID);
      }
    }

    return Token(END);
  }

  // method to get a number value token lexer.getNumberValue()
  int getNumberValue() const { return numberValue; }

 private:
  std::string text;
  std::size_t pos;
  char currentChar;
  int numberValue;

  void advance() { //advance helper method to move through input string
    pos++; 
    if (pos >= text.size()) {
      currentChar = '\0';
    } else {
      currentChar = text[pos];
    }
  }

  void skipWhitespace() { // method to skip white space
    while (currentChar != '\0' &&
           std::isspace(static_cast<unsigned char>(currentChar))) {
      advance();
    }
  }

  int parseNumber() { // Number: [0-9.]+
    std::string numStr;
    while (currentChar != '\0' &&
           std::isdigit(static_cast<unsigned char>(currentChar))) {
      numStr += currentChar;
      advance();
    }
    try {
      return std::stoi(numStr);
    } catch (const std::invalid_argument& e) {
      std::cerr << "Invalid number: " << e.what() << std::endl;
      throw;
    } catch (const std::out_of_range& e) {
      std::cerr << "Number out of range: " << e.what() << std::endl;
      throw;
    }
  }
};
