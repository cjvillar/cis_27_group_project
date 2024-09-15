#pragma once

#include "config.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

class IRGenVisitor : public ASTVisitor {
  public:
    IRGenVisitor(llvm::Module* module);
    void visit(NumExprAST& numExpr) override;
    void visit(BinOpExprAST& binOpExpr) override;
    llvm::Value* getValue() { return value; }

  private:
    llvm::Module* module;
    llvm::IRBuilder<> builder;
    llvm::Type* Int32Ty;
    llvm::Constant* Int32Zero;
    llvm::Value* value;
};