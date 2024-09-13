
#include "config.h"

std::ostream& operator<<(std::ostream& os, const TokenKind& tokenKind) {
    switch(tokenKind) {
        case TokenKind::NUMBER:
            os << "NUMBER";
            break;
        case TokenKind::PLUS:
            os << "PLUS";
            break;
        case TokenKind::MINUS:
            os << "MINUS";
            break;
        case TokenKind::MULTIPLY:
            os << "MULTIPLY";
            break;
        case TokenKind::DIVIDE:
            os << "DIVIDE";
            break;
        case TokenKind::LPAREN:
            os << "LPAREN";
            break;
        case TokenKind::RPAREN:
            os << "RPAREN";
            break;
        case TokenKind::INVALID:
            os << "INVALID";
            break;
        case TokenKind::END:
            os << "END";
            break;
    }
    return os;
}

Token::Token() : kind(TokenKind::INVALID), val(std::nullopt) {}
Token::Token(TokenKind kind) : kind(kind), val(std::nullopt) {}
Token::Token(TokenKind kind, std::optional<int> val) : kind(kind), val(val) {}

TokenKind Token::getKind() const { return kind; }
std::optional<int> Token::getValue() const { return val; }

std::ostream& operator<<(std::ostream& os, std::optional<int> val) {
    if (val.has_value()) {
        std::cout << val.value();
    } else {
        std::cout << "no value";
    }
    return os;
}

Lexer::Lexer(const std::string& text) 
    : text(text),
      pos(0),
      currentChar(text.empty() ? '\0' : text[0]),
      numberValue(0) {}

Token Lexer::getNextToken() {
    while (currentChar != '\0') {
        if (std::isspace(static_cast<unsigned char>(currentChar))) {
            skipWhitespace();
            continue;
        }

        if (std::isdigit(static_cast<unsigned char>(currentChar))) {
            numberValue = parseNumber();
            return Token(TokenKind::NUMBER, numberValue);
        }

        switch (currentChar) {
            case '+':
                advance();
                return Token(TokenKind::PLUS);
            case '-':
                advance();
                return Token(TokenKind::MINUS);
            case '*':
                advance();
                return Token(TokenKind::MULTIPLY);
            case '/':
                advance();
                return Token(TokenKind::DIVIDE);
            case '(':
                advance();
                return Token(TokenKind::LPAREN);
            case ')':
                advance();
                return Token(TokenKind::RPAREN);
            default:
                advance();
                return Token(TokenKind::INVALID);
        }
    }

    return Token(TokenKind::END);
}

int Lexer::getNumberValue() const { return numberValue; }

void Lexer::advance() {
    pos++;
    currentChar = (pos >= text.size()) ? '\0' : text[pos];
}

void Lexer::skipWhitespace() {
    while (currentChar != '\0' && std::isspace(static_cast<unsigned char>(currentChar))) {
        advance();
    }
}

int Lexer::parseNumber() {
    std::string numStr;
    while (currentChar != '\0' && std::isdigit(static_cast<unsigned char>(currentChar))) {
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
