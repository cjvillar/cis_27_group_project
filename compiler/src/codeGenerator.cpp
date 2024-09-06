// #include "config.h"

// // Definitions for CodeGenerator class
// std::string CodeGenerator::generate(const std::vector<IRInstruction>& ir) {
//   std::ostringstream code;

//   code << "section .text\n";
//   code << "global _start\n";
//   code << "\n";
//   code << "_start:\n";

//   for (const auto& instruction : ir) {
//     switch (instruction.op) {
//       case IRInstruction::OpType::MOV:
//         code << "    mov rax, " << instruction.lhs << "\n";
//         break;
//       case IRInstruction::OpType::ADD:
//         code << "    add rax, " << instruction.rhs << "\n";
//         break;
//       case IRInstruction::OpType::SUB:
//         code << "    sub rax, " << instruction.rhs << "\n";
//         break;
//       case IRInstruction::OpType::MULTIPLY:
//         code << "    imul rax, " << instruction.rhs << "\n";
//         break;
//       case IRInstruction::OpType::DIVIDE:
//         code << "    idiv rax, " << instruction.rhs << "\n";
//         break;
//       default:
//         throw std::runtime_error("Unsupported IR operation");
//     }
//   }

//   code << "\n";
//   code << "    mov rdi, 0\n";   // Exit code
//   code << "    mov rax, 60\n";  // syscall number for exit
//   code << "    syscall\n";      // call the kernel

//   return code.str();
// }

#include "config.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ExecutionEngine/Orc/ThreadSafeModule.h>
#include <llvm/ExecutionEngine/Orc/LLJIT.h>

std::string CodeGenerator::generate(const std::vector<IRInstruction>& ir) {
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder(context);
    auto module = std::make_unique<llvm::Module>("HenloModule", context);

    llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getVoidTy(), false);
    llvm::Function *mainFunction = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", *module);
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", mainFunction);
    builder.SetInsertPoint(entry);

    for (const auto& instruction : ir) {
        llvm::Value *lhs = builder.getInt64(std::stoll(instruction.lhs));
        llvm::Value *rhs = builder.getInt64(std::stoll(instruction.rhs));

        switch (instruction.op) {
            case IRInstruction::OpType::MOV:
                builder.CreateAlloca(lhs->getType(), nullptr, "tmp");
                builder.CreateStore(lhs, builder.CreateAlloca(lhs->getType()));
                break;
            case IRInstruction::OpType::ADD:
                builder.CreateAdd(lhs, rhs);
                break;
            case IRInstruction::OpType::SUB:
                builder.CreateSub(lhs, rhs);
                break;
            case IRInstruction::OpType::MULTIPLY:
                builder.CreateMul(lhs, rhs);
                break;
            case IRInstruction::OpType::DIVIDE:
                builder.CreateSDiv(lhs, rhs);
                break;
            default:
                throw std::runtime_error("Unsupported IR operation");
        }
    }

    builder.CreateRetVoid();

    // Verify the generated code
    std::string error;
    if (llvm::verifyModule(*module, &llvm::errs())) {
        llvm::errs() << "Error generating LLVM IR\n";
        return "";
    }

    // Output the LLVM IR to a file or string
    std::string irStr;
    llvm::raw_string_ostream irStream(irStr);
    module->print(irStream, nullptr);

    return irStr;
}
