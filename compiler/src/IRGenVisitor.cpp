#include "config.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/BasicBlock.h"


IRGenVisitor::IRGenVisitor(llvm::Module* module) : 
  module(module), builder(module->getContext()) {
    VoidTy = llvm::Type::getVoidTy(module->getContext());
    Int32Ty = llvm::Type::getInt32Ty(module->getContext());
    PtrTy = llvm::PointerType::getUnqual(module->getContext());
    Int32Zero = llvm::ConstantInt::get(Int32Ty, 0, true);
  }

void IRGenVisitor::run(std::unique_ptr<ExprAST>& exprAST) {
  llvm::FunctionType *MainFnTy = llvm::FunctionType::get(
    Int32Ty, {Int32Ty}, false
  );
  llvm::Function *MainFn = llvm::Function::Create(
    MainFnTy, llvm::GlobalValue::ExternalLinkage, "main", module
  );
  // Currently VSCode intellisense reports an incomplete type error
  // for llvm::BasicBlock, but compilation reports no errors
  llvm::BasicBlock* basicBlock = llvm::BasicBlock::Create(
    module->getContext(), "entry", MainFn
  );
  builder.SetInsertPoint(basicBlock);

  exprAST->accept(*this);

  llvm::FunctionType *WriteFnTy = llvm::FunctionType::get(
    VoidTy, {Int32Ty}, false
  );
  llvm::Function *WriteFn = llvm::Function::Create(
    WriteFnTy, llvm::GlobalValue::ExternalLinkage,
    "write_fn", module
  );
  // Currently VSCode intellisense reports argument type mismatch,
  // but no compilation errors have been detected.
  builder.CreateCall(WriteFnTy, WriteFn, {value});
  builder.CreateRet((llvm::Value*)Int32Zero);
}

// empty method for base-class to enable calls on base-class ptrs.
void IRGenVisitor::visit(ExprAST& exprAST) {}

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