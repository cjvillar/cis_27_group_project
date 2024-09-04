#include "config.h"

// Definitions for CodeGenerator class
std::string CodeGenerator::generate(const std::vector<IRInstruction>& ir) {
  std::ostringstream code;

  code << "section .text\n";
  code << "global _start\n";
  code << "\n";
  code << "_start:\n";

  for (const auto& instruction : ir) {
    switch (instruction.op) {
      case IRInstruction::OpType::MOV:
        code << "    mov rax, " << instruction.lhs << "\n";
        break;
      case IRInstruction::OpType::ADD:
        code << "    add rax, " << instruction.rhs << "\n";
        break;
      case IRInstruction::OpType::SUB:
        code << "    sub rax, " << instruction.rhs << "\n";
        break;
      case IRInstruction::OpType::MULTIPLY:
        code << "    imul rax, " << instruction.rhs << "\n";
        break;
      case IRInstruction::OpType::DIVIDE:
        code << "    idiv rax, " << instruction.rhs << "\n";
        break;
      default:
        throw std::runtime_error("Unsupported IR operation");
    }
  }

  code << "\n";
  code << "    mov rdi, 0\n";   // Exit code
  code << "    mov rax, 60\n";  // syscall number for exit
  code << "    syscall\n";      // call the kernel

  return code.str();
}
