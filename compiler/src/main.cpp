#include "config.h"

int main(int argc, char* argv[]) {
  // Check if an input file is provided
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file.henlo>" << std::endl;
    return 1;
  }

  // Attempt to open the input file
  std::ifstream inputFile(argv[1]);
  if (!inputFile.is_open()) {
    std::cerr << "Failed to open input file: " << argv[1] << std::endl;
    return 1;
  }

  // Read the entire file into a string
  std::string input((std::istreambuf_iterator<char>(inputFile)),
                    std::istreambuf_iterator<char>());

  // Tokenize the input
  Lexer lexer(input);
  std::vector<ReservedToken> tokens;
  std::vector<std::string> tokenValues;

  try {
    tokens = lexer.tokenize();
    tokenValues = lexer.getTokenValues();
  } catch (const std::exception& ex) {
    std::cerr << "Lexical analysis error: " << ex.what() << std::endl;
    return 1;
  }

  // Parse the tokens into an AST
  Parser parser(tokens, tokenValues);
  AST ast;
  try {
    ast = parser.parse();
    ast.print();  // Print the AST for verification
  } catch (const std::exception& ex) {
    std::cerr << "Parsing error: " << ex.what() << std::endl;
    return 1;
  }

  // Perform semantic analysis on the AST
  SemanticAnalyzer semanticAnalyzer;
  try {
    semanticAnalyzer.analyze(ast);
    std::cout << "Semantic analysis passed." << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "Semantic error: " << ex.what() << std::endl;
    return 1;
  }

  // Generate intermediate representation (IR) from the AST
  std::vector<IRInstruction> ir = parser.generateIR(ast);

  // Generate assembly code from the IR
  CodeGenerator codeGen;
  std::string assemblyCode = codeGen.generate(ir);

  // Write the assembly code to an output file
  std::ofstream outFile("output.asm");
  if (!outFile) {
    std::cerr << "Failed to open output.asm for writing." << std::endl;
    return 1;
  }
  outFile << assemblyCode;
  outFile.close();

  std::cout << "Assembly code generated successfully." << std::endl;

  // Assemble and link the assembly code into an executable
  int result = system("clang -o output output.asm");
  if (result != 0) {
    std::cerr << "Failed to create executable." << std::endl;
    return 1;
  }

  std::cout << "Executable created successfully." << std::endl;

  return 0;
}
