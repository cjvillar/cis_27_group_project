#pragma once

#include <memory>
#include "Lexer.h"

class ExprAST;
class NumExprAST;
class BinOpExprAST;

class ASTVisitor {
  public:
    virtual void visit(NumExprAST& numExprAST) = 0;
    virtual void visit(BinOpExprAST& binOpExerAST) = 0;
  private:
};

class ExprAST {
  public:
    virtual ~ExprAST() = default;
    // Here I'm using a separate print function for these classes because 
    // I can't figure out how to properly overload `operator<<` to apply
    // to the children of `BinOpExprAST` instances.
    // Note that this has to be called with an empty string argument
    // to get the right indentation levels. This is because it is applied 
    // recursively to the children of `BinOpExprAST`.
    virtual void print(std::string indent) = 0;
    virtual void accept(ASTVisitor& irGen) = 0;
};

class NumExprAST : public ExprAST {
  public:
    NumExprAST(Token token) {
      // Using pre-validation to check whether a token can form
      // a valid Number node. Might be worth it to subclass `Token` instead.
      if (token.getValue().has_value() && token.getKind() == TokenKind::NUMBER) {
        value = token.getValue().value();
      }
    }

    int getValue() const { return value; }
    void print(std::string indent) override { std::cout << getValue() << "\n"; }
    void accept(ASTVisitor& irGen) {
      irGen.visit(*this);
    }

  private:
    int value;
};

class BinOpExprAST : public ExprAST {
  public:
    BinOpExprAST(Token token, std::unique_ptr<ExprAST>& left, std::unique_ptr<ExprAST>& right) 
      : kind(token.getKind()), left(std::move(left)), right(std::move(right)) {}

    TokenKind getKind() const { return kind; }

    std::unique_ptr<ExprAST> getLeft() { return std::move(left); }
    std::unique_ptr<ExprAST> getRight() { return std::move(right); }

    void print(std::string indent) override {
      std::cout << "+" << getKind() << "\n";
      std::cout << indent << "|---";
      left->print("    " + indent);
      std::cout << indent << "|---";
      right->print("    " + indent);
    }

    void accept(ASTVisitor& irGen) {
      irGen.visit(*this);
    }

  private:
    TokenKind kind;
    std::unique_ptr<ExprAST> left, right;
};
