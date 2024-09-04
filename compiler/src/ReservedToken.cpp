#include "config.h"

// enum class ReservedToken : std::uint8_t {
//   BORK,
//   NUMBER,
//   PLUS,
//   MINUS,
//   MULTIPLY,
//   DIVIDE,
//   EQUAL,
//   IDENTIFIER,
//   OPERATOR
// };

// Define the keyword tokens array
const std::array<std::pair<ReservedToken, std::string_view>, 1> keywordTokens{
    {{ReservedToken::BORK, "bork"}}};

// Define the operator tokens array
const std::array<std::pair<ReservedToken, std::string_view>, 5> operatorTokens{
    {{ReservedToken::OPERATOR, "+"},
     {ReservedToken::OPERATOR, "-"},
     {ReservedToken::OPERATOR, "*"},
     {ReservedToken::OPERATOR, "/"},
     {ReservedToken::OPERATOR, "="}}};

// Function to find the matching keyword token from a string
ReservedToken findKeyword(std::string_view str) {
    auto it = std::find_if(
        keywordTokens.begin(), keywordTokens.end(),
        [&str](const std::pair<ReservedToken, std::string_view>& pair) {
            return pair.second == str;
        });
    if (it != keywordTokens.end()) {
        return it->first;
    }
    return ReservedToken::IDENTIFIER;  // Default if not found
}

// Function to find the matching operator token from a string
ReservedToken findOperator(std::string_view str) {
    auto it = std::find_if(
        operatorTokens.begin(), operatorTokens.end(),
        [&str](const std::pair<ReservedToken, std::string_view>& pair) {
            return pair.second == str;
        });
    if (it != operatorTokens.end()) {
        return it->first;
    }
    return ReservedToken::IDENTIFIER;  // Default if not found
}
