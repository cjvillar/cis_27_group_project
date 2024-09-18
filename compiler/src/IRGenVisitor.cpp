#include "config.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"


IRGenVisitor::IRGenVisitor(llvm::Module* module) : 
  module(module), builder(module->getContext()) {
    Int32Ty = llvm::Type::getInt32Ty(module->getContext());
    Int32Zero = llvm::ConstantInt::get(Int32Ty, 0, true);
  }

void IRGenVisitor::visit(NumExprAST& numExpr) {
  // I'm having to cast this to get VSCode to stop complaining but 
  // it should compile without the cast
  value = (llvm::Value*)llvm::ConstantInt::get(Int32Ty, numExpr.getValue());
}

void IRGenVisitor::visit(BinOpExprAST& binOpExpr) {
  binOpExpr.getLeft()->accept(*this);
  llvm::Value* left = value;
  binOpExpr.getRight()->accept(*this);
  llvm::Value* right = value;
  switch(binOpExpr.getKind()) {
    case TokenKind::PLUS:
      value = builder.CreateNSWAdd(left, right);
      break;
    case TokenKind::MINUS:
      value = builder.CreateNSWSub(left, right);
      break;
    case TokenKind::MULTIPLY:
      value = builder.CreateNSWMul(left, right);
      break;
    case TokenKind::DIVIDE:
      value = builder.CreateSDiv(left, right);
      break;
  }
}