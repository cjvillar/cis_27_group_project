#ifndef PARSER_H
#define PARSER_H


#include "config.h"

struct Expression {
  ReservedToken op;
  std::string lhs;  // This could be either an identifier or a number
  std::string rhs;  // This could be either an identifier or a number
  bool isNumberLHS;
  bool isNumberRHS;
};

struct Statement {
  ReservedToken keyword;
  Expression expr;
};

class AST {
 public:
  void addStatement(const Statement& stmt);
  const std::vector<Statement>& getStatements() const;
  void print() const;

 private:
  std::vector<Statement> statements;
};

struct IRInstruction {
  enum class OpType { ADD, SUB, MOV, MULTIPLY, DIVIDE };

  OpType op;
  std::string lhs;
  std::string rhs;
  std::string size;
};

class SemanticAnalyzer {
 public:
  void analyze(const AST& ast);

 private:
  void checkExpression(const Expression& expr);
};

class Parser {
public:
    Parser(const std::vector<ReservedToken>& tokens, const std::vector<std::string>& tokenValues);

    Statement parseStatement();
    AST parse();
    std::vector<IRInstruction> generateIR(const AST& ast);

private:
    std::vector<ReservedToken> tokens;
    std::vector<std::string> tokenValues;
    size_t currentIndex;

    ReservedToken currentToken() const;
    void nextToken();
    std::string getTokenValue() const;
};

#endif // PARSER_H

