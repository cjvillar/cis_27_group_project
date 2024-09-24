#pragma once

#include "config.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

class IRGenVisitor : public ASTVisitor {
  public:
    IRGenVisitor(llvm::Module* module);
    void run(std::unique_ptr<ExprAST>& exprAST);
    void visit(ExprAST& exprAST) override;
    void visit(NumExprAST& numExpr) override;
    void visit(BinOpExprAST& binOpExpr) override;
    llvm::Value* getValue() { return value; }

  private:
    llvm::Module* module;
    llvm::IRBuilder<> builder;
    llvm::Type* VoidTy;
    llvm::Type* Int32Ty;
    llvm::PointerType* PtrTy;
    llvm::Constant* Int32Zero;
    llvm::Value* value;
};