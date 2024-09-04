#include "config.h"

// Definitions for AST class
void AST::addStatement(const Statement& stmt) {
  statements.push_back(stmt);
}

const std::vector<Statement>& AST::getStatements() const {
  return statements;
}

void AST::print() const {
  for (const auto& stmt : statements) {
    std::cout << "Statement: " << static_cast<int>(stmt.keyword) << std::endl;
    std::cout << "  Expression: " << stmt.expr.lhs << " "
              << static_cast<int>(stmt.expr.op) << " " << stmt.expr.rhs
              << std::endl;
  }
}

// Definitions for Parser class
Parser::Parser(const std::vector<ReservedToken>& tokens,
               const std::vector<std::string>& tokenValues)
    : tokens(tokens), tokenValues(tokenValues), currentIndex(0) {}

Statement Parser::parseStatement() {
  if (currentToken() == ReservedToken::BORK) {
    nextToken();

    // Parse left-hand side (LHS)
    std::string lhs;
    bool isNumberLHS = false;

    if (currentToken() == ReservedToken::NUMBER) {
      lhs = getTokenValue();
      isNumberLHS = true;
      nextToken();
    } else if (currentToken() == ReservedToken::IDENTIFIER) {
      lhs = getTokenValue();
      isNumberLHS = false;
      nextToken();
    } else {
      throw std::runtime_error("Expected identifier or number");
    }

    // Parse operator
    ReservedToken op;
    if (currentToken() == ReservedToken::PLUS ||
        currentToken() == ReservedToken::MINUS ||
        currentToken() == ReservedToken::MULTIPLY ||
        currentToken() == ReservedToken::DIVIDE ||
        currentToken() == ReservedToken::EQUAL) {
      op = currentToken();
      nextToken();
    } else {
      throw std::runtime_error("Expected operator");
    }

    // Parse right-hand side (RHS)
    std::string rhs;
    bool isNumberRHS = false;

    if (currentToken() == ReservedToken::NUMBER) {
      rhs = getTokenValue();
      isNumberRHS = true;
      nextToken();
    } else if (currentToken() == ReservedToken::IDENTIFIER) {
      rhs = getTokenValue();
      isNumberRHS = false;
      nextToken();
    } else {
      throw std::runtime_error("Expected identifier or number");
    }

    return Statement{ReservedToken::BORK,
                     Expression{op, lhs, rhs, isNumberLHS, isNumberRHS}};
  }
  throw std::runtime_error("Syntax error in statement");
}

AST Parser::parse() {
  AST ast;
  while (currentIndex < tokens.size()) {
    Statement stmt = parseStatement();
    ast.addStatement(stmt);
  }
  return ast;
}

std::vector<IRInstruction> Parser::generateIR(const AST& ast) {
  std::vector<IRInstruction> ir;
  for (const auto& stmt : ast.getStatements()) {
    if (stmt.keyword == ReservedToken::BORK) {
      IRInstruction instr;
      instr.lhs = stmt.expr.lhs;
      instr.rhs = stmt.expr.rhs;

      switch (stmt.expr.op) {
        case ReservedToken::PLUS:
          instr.op = IRInstruction::OpType::ADD;
          break;
        case ReservedToken::MINUS:
          instr.op = IRInstruction::OpType::SUB;
          break;
        case ReservedToken::MULTIPLY:
          instr.op = IRInstruction::OpType::MULTIPLY;
          break;
        case ReservedToken::DIVIDE:
          instr.op = IRInstruction::OpType::DIVIDE;
          break;
        case ReservedToken::EQUAL:
          instr.op = IRInstruction::OpType::MOV;
          break;
        default:
          throw std::runtime_error("Unsupported operation in IR");
      }

      ir.push_back(instr);
    }
  }
  return ir;
}

// Definitions for SemanticAnalyzer class
void SemanticAnalyzer::analyze(const AST& ast) {
  for (const auto& stmt : ast.getStatements()) {
    if (stmt.keyword == ReservedToken::BORK) {
      checkExpression(stmt.expr);
    }
  }
}

ReservedToken Parser::currentToken() const {
  if (currentIndex < tokens.size()) {
    return tokens[currentIndex];
  }
  throw std::out_of_range("No more tokens");
}

void Parser::nextToken() {
  if (currentIndex < tokens.size()) {
    ++currentIndex;
  }
}

std::string Parser::getTokenValue() const {
  if (currentIndex < tokenValues.size()) {
    return tokenValues[currentIndex];
  }
  throw std::out_of_range("No more token values");
}

void SemanticAnalyzer::checkExpression(const Expression& expr) {
  if (expr.lhs.empty() || expr.rhs.empty()) {
    throw std::runtime_error("Semantic error: Invalid expression.");
  }
}

