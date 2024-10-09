#include "config.h"

// get the file name from the command line
static llvm::cl::opt<std::string> inputFile(llvm::cl::Positional,
                                            llvm::cl::desc("<input file>"),
                                            llvm::cl::init(""));

int main(int argc, const char* argv[]) {
  llvm::InitLLVM X(argc, argv);
  llvm::cl::ParseCommandLineOptions(argc, argv);

  // open input file
  std::ifstream file(inputFile);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << inputFile << std::endl;
    return 1;
  }

  // read file contents into a string
  std::string inputExpression((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());

  // close file
  file.close();

  // check for empty input
  if (inputExpression.empty()) {
    std::cerr << "Error: Input expression is empty" << std::endl;
    return 1;
  }

  // parse input expression using the Parser
  Parser parser(inputExpression);
  parser.parse();
  std::unique_ptr<ExprAST> ast = std::move(parser.getResult());

  // LLVM module
  std::unique_ptr<llvm::LLVMContext> context =
      std::make_unique<llvm::LLVMContext>();
  llvm::Module* module = new llvm::Module("arithmetic", *context);
  IRGenVisitor irGen(module);

  // iR generation
  irGen.visit(*ast);
  irGen.run(ast);

  // output to console (removed for file input below)
  // module->print(llvm::outs(), nullptr);

  //create an output file and write the IR to it
  //this may be usefule later for IR.ll --> ASM executable, idk
  std::error_code errorCode;
  llvm::raw_fd_ostream OS("output.ll", errorCode);
  if (errorCode) {
    std::cerr << "Error opening file: " << errorCode.message() << std::endl;
    return 1;
  }

  // print module to the file using raw_fd_ostream
  module->print(OS, nullptr);
  
  delete module;

  return 0;
}
