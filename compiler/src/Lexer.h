#pragma once

#include "config.h"

enum class TokenKind {
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

std::ostream& operator<<(std::ostream& os, const TokenKind& tokenKind);

class Token {
public:
    Token();
    Token(TokenKind kind);
    Token(TokenKind kind, std::optional<int> val);
    TokenKind getKind() const;
    std::optional<int> getValue() const;

private:
    TokenKind kind;
    std::optional<int> val;
};

std::ostream& operator<<(std::ostream& os, std::optional<int> val);

class Lexer {
public:
    Lexer(const std::string& text);
    Token getNextToken();
    int getNumberValue() const;

private:
    std::string text;
    std::size_t pos;
    char currentChar;
    int numberValue;

    void advance();
    void skipWhitespace();
    int parseNumber();
};


