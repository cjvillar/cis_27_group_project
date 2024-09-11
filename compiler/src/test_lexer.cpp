//used only to test the output of the lexer. 
// Will not include if any merge to main

#include "Lexer.cpp"  // Include the lexer implementation
#include <iostream>

int main() {
    //test code string
    std::string input = "12 + 24 - (3 * 4) / 06"; // should ignore leading 0
    Lexer lexer(input);

    Tokens token;
    while ((token = lexer.getNextToken()) != Tokens::END) {
        switch (token) {
            case Tokens::NUMBER:
                std::cout << "NUMBER(" << lexer.getNumberValue() << ")\n";
                break;
            case Tokens::PLUS:
                std::cout << "PLUS\n";
                break;
            case Tokens::MINUS:
                std::cout << "MINUS\n";
                break;
            case Tokens::MULTIPLY:
                std::cout << "MULTIPLY\n";
                break;
            case Tokens::DIVIDE:
                std::cout << "DIVIDE\n";
                break;
            case Tokens::LPAREN:
                std::cout << "LPAREN\n";
                break;
            case Tokens::RPAREN:
                std::cout << "RPAREN\n";
                break;
            case Tokens::INVALID:
                std::cout << "INVALID\n";
                break;
            default:
                break;
        }
    }

    return 0;
}
