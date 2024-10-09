#pragma once

// standard headers
#include <cctype>
#include <iostream>
#include <memory>
#include <optional>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>

// llvm (I need to "clean up")
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/Error.h"
#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ADT/DenseMap.h"

//LLVM  file support
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/SourceMgr.h"

// includes
#include "Lexer.h"
#include "AST.h"
#include "Parser.h"
#include "IRGenVisitor.h"


