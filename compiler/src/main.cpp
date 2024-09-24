#include "config.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LLVMContext.h"

static llvm::cl::opt<std::string>
  input(llvm::cl::Positional,
      llvm::cl::desc("<input expression>"),
      llvm::cl::init(""));

int main(int argc, const char* argv[]) {
  llvm::InitLLVM X(argc, argv);
  llvm::cl::ParseCommandLineOptions(argc, argv);

  Parser parser(input);
  parser.parse();
  std::unique_ptr<ExprAST> ast = std::move(parser.getResult());
  
  std::unique_ptr<llvm::LLVMContext> context = std::make_unique<llvm::LLVMContext>();
  llvm::Module* module = new llvm::Module("arithmetic", *context);
  IRGenVisitor irGen(module);
  // irGen.visit(*ast);
  irGen.run(ast);
  module->print(llvm::outs(), nullptr);

  delete module;
}
