// #include "config.h"

// int main(int argc, char* argv[]) {
//   // Check if an input file is provided
//   if (argc < 2) {
//     std::cerr << "Usage: " << argv[0] << " <input_file.henlo>" << std::endl;
//     return 1;
//   }

//   // Attempt to open the input file
//   std::ifstream inputFile(argv[1]);
//   if (!inputFile.is_open()) {
//     std::cerr << "Failed to open input file: " << argv[1] << std::endl;
//     return 1;
//   }

//   // Read the entire file into a string
//   std::string input((std::istreambuf_iterator<char>(inputFile)),
//                     std::istreambuf_iterator<char>());

//   // Tokenize the input
//   Lexer lexer(input);
//   std::vector<ReservedToken> tokens;
//   std::vector<std::string> tokenValues;

//   try {
//     tokens = lexer.tokenize();
//     tokenValues = lexer.getTokenValues();
//   } catch (const std::exception& ex) {
//     std::cerr << "Lexical analysis error: " << ex.what() << std::endl;
//     return 1;
//   }

//   // Parse the tokens into an AST
//   Parser parser(tokens, tokenValues);
//   AST ast;
//   try {
//     ast = parser.parse();
//     ast.print();  // Print the AST for verification
//   } catch (const std::exception& ex) {
//     std::cerr << "Parsing error: " << ex.what() << std::endl;
//     return 1;
//   }

//   // Perform semantic analysis on the AST
//   SemanticAnalyzer semanticAnalyzer;
//   try {
//     semanticAnalyzer.analyze(ast);
//     std::cout << "Semantic analysis passed." << std::endl;
//   } catch (const std::exception& ex) {
//     std::cerr << "Semantic error: " << ex.what() << std::endl;
//     return 1;
//   }

//   // Generate intermediate representation (IR) from the AST
//   std::vector<IRInstruction> ir = parser.generateIR(ast);

//   // Generate assembly code from the IR
//   CodeGenerator codeGen;
//   std::string assemblyCode = codeGen.generate(ir);

//   // Write the assembly code to an output file
//   std::ofstream outFile("output.asm");
//   if (!outFile) {
//     std::cerr << "Failed to open output.asm for writing." << std::endl;
//     return 1;
//   }
//   outFile << assemblyCode;
//   outFile.close();

//   std::cout << "Assembly code generated successfully." << std::endl;

//   // Assemble and link the assembly code into an executable
//   int result = system("clang -o output output.asm");
//   if (result != 0) {
//     std::cerr << "Failed to create executable." << std::endl;
//     return 1;
//   }

//   std::cout << "Executable created successfully." << std::endl;

//   return 0;
// }


#include "config.h"
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/ExecutionEngine/Orc/ThreadSafeModule.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

int main() {
    llvm::LLVMContext Context;
    auto Module = std::make_unique<llvm::Module>("main_module", Context);
    llvm::IRBuilder<> Builder(Context);

    try {
        // Create a simple function
        llvm::FunctionType *FuncType = llvm::FunctionType::get(Builder.getVoidTy(), false);
        llvm::Function *Func = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, "my_function", *Module);
        llvm::BasicBlock *Entry = llvm::BasicBlock::Create(Context, "entry", Func);
        Builder.SetInsertPoint(Entry);
        Builder.CreateRetVoid();

        // Verify the module
        if (llvm::verifyModule(*Module, &llvm::errs())) {
            llvm::errs() << "Module verification failed\n";
            return 1;
        }

        // Initialize LLVM
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmPrinter();
        llvm::InitializeNativeTargetAsmParser();

        // Create the JIT instance
        auto JIT = llvm::orc::LLJITBuilder().create();
        if (!JIT) {
            llvm::errs() << "Failed to create LLJIT\n";
            return 1;
        }

        // Create a ThreadSafeModule
        auto TSCtx = llvm::orc::ThreadSafeContext(std::make_unique<llvm::LLVMContext>());
        auto ThreadSafeModule = llvm::orc::ThreadSafeModule(std::move(Module), TSCtx);

        // Add the module to the JIT
        if (auto Err = JIT->getMainJITDylib().add(llvm::orc::ThreadSafeModule(std::move(ThreadSafeModule), TSCtx))) {
            llvm::errs() << "Failed to add IR module: " << toString(std::move(Err)) << "\n";
            return 1;
        }

        // Look up the function
        auto FuncSymbol = JIT->lookup("my_function");
        if (!FuncSymbol) {
            llvm::errs() << "Failed to lookup function\n";
            return 1;
        }

        llvm::outs() << "Function address: " << FuncSymbol->getAddress() << "\n";

    } catch (const std::exception& ex) {
        std::cerr << "LLVM error: " << ex.what() << std::endl;
        return 1;
    }

    std::cout << "LLVM processing completed successfully." << std::endl;
    return 0;
}
