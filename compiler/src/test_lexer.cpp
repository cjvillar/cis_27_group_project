//used only to test the output of the lexer. 
// Will not include if any merge to main

#include "Lexer.cpp"  // Include the lexer implementation
#include <iostream>

int main() {
    //test code string
    std::string input = "12 + 24 - (3 * 4) / 06"; // should ignore leading 0
    Lexer lexer(input);

    Token token;
    while ((token = lexer.getNextToken()).getKind() != TokenKind::END) {
        switch (token.getKind()) {
            case TokenKind::NUMBER:
                std::cout << "NUMBER(" << token.getValue() << ")\n";
                break;
            case TokenKind::PLUS:
                std::cout << "PLUS\n";
                break;
            case TokenKind::MINUS:
                std::cout << "MINUS\n";
                break;
            case TokenKind::MULTIPLY:
                std::cout << "MULTIPLY\n";
                break;
            case TokenKind::DIVIDE:
                std::cout << "DIVIDE\n";
                break;
            case TokenKind::LPAREN:
                std::cout << "LPAREN\n";
                break;
            case TokenKind::RPAREN:
                std::cout << "RPAREN\n";
                break;
            case TokenKind::INVALID:
                std::cout << "INVALID\n";
                break;
            default:
                break;
        }
    }

    return 0;
}
