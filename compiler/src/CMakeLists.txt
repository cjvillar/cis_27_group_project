cmake_minimum_required(VERSION 3.20.0)
project(Compiler)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_executable(Compiler 
    Lexer.cpp 
    Parser.cpp
    IRGenVisitor.cpp 
    main.cpp
)

# Disable run-time type information.
# I think this is needed because my binaries are
# built without it. Otherwise generates ld typeinfo error.
# see https://discourse.llvm.org/t/undefined-reference-to-typeinfo-for-llvm-genericoptionvalue/71526/3
set(NO_RTTI "-fno-rtti")
add_definitions(${NO_RTTI})

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_include_directories(Compiler PUBLIC ${LLVM_INCLUDE_DIRS})
target_link_libraries(Compiler ${llvm_libs})

# This compiler flag generates debug symbols that cooperate with valgrind under Linux.
set_source_files_properties(IRGenVisitor_test.cpp PROPERTIES COMPILE_FLAGS "-gdwarf-4")
