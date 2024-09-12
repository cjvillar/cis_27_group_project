#include <cctype>
#include <iostream>
#include <optional> //not curenty used
#include <stdexcept>
#include <string>

// TokenType class to hold type and value
// Enum classes strongly typed and strongly scoped
enum class TokenType {
  NUMBER,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  LPAREN,
  RPAREN,
  END,
  INVALID
};

class Token {
 public:
  Token(TokenType type, const std::string& value = "")
      // Token(TokenType type, std::optional<int> value = std::nullopt)
      // retuns empty string by defalut, but many options here.
      // I could not get <optional> to work on my end
      : type(type), value(value) {}

  TokenType getType() const { return type; }
  std::string getValue() const { return value; }

 private:
  TokenType type;
  std::string value;
};

class Lexer {
 public:
  Lexer(const std::string& text)
      : text(text),
        pos(0),
        currentChar(text.empty() ? '\0' : text[0]),
        numberValue(0) {}

  Token getNextToken() {
    while (currentChar != '\0') {
      if (std::isspace(static_cast<unsigned char>(currentChar))) {
        skipWhitespace();
        continue;
      }

      if (std::isdigit(static_cast<unsigned char>(currentChar))) {
        numberValue = parseNumber();
        return Token(TokenType::NUMBER, std::to_string(numberValue));
      }

      switch (currentChar) {
        case '+':
          advance();
          return Token(TokenType::PLUS);
        case '-':
          advance();
          return Token(TokenType::MINUS);
        case '*':
          advance();
          return Token(TokenType::MULTIPLY);
        case '/':
          advance();
          return Token(TokenType::DIVIDE);
        case '(':
          advance();
          return Token(TokenType::LPAREN);
        case ')':
          advance();
          return Token(TokenType::RPAREN);
        default:
          advance();
          return Token(TokenType::INVALID);
      }
    }

    return Token(TokenType::END);
  }

  int getNumberValue() const { return numberValue; }

 private:
  std::string text;
  size_t pos;
  char currentChar;
  int numberValue;

  void advance() { 
    pos++;
    if (pos >= text.size()) {
      currentChar = '\0';
    } else {
      currentChar = text[pos];
    }
  }

  void skipWhitespace() {
    while (currentChar != '\0' &&
           std::isspace(static_cast<unsigned char>(currentChar))) {
      advance();
    }
  }

  int parseNumber() {
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
