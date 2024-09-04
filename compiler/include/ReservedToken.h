#ifndef RESERVEDTOKEN_H
#define RESERVEDTOKEN_H

#include "config.h"

// Enum class for reserved tokens
enum class ReservedToken : std::uint8_t {
  BORK,
  NUMBER,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  EQUAL,
  IDENTIFIER,
  OPERATOR
};

// Function to find the matching keyword token from a string
ReservedToken findKeyword(std::string_view str);

// Function to find the matching operator token from a string
ReservedToken findOperator(std::string_view str);

#endif  // RESERVEDTOKEN_H
