# Test Branch Instructions


Dir structure:
```
compiler/
├── CMakeLists.txt
├── llvm-project-llvmorg-18.1.8
├── include/
│   ├── ReservedToken.h
│   ├── Lexer.h
    ├── CodeGenerator.h
│   ├── Parser.h
│   └── config.h
├── src/
│   ├── main.cpp
    ├── CodeGenerator.cpp
│   ├── Lexer.cpp
│   └── Parser.cpp
└── example.henlo
```

### LLVM:
https://github.com/llvm/llvm-project/releases/tag/llvmorg-18.1.8


### Compilation Instructions:
1. **Navigate to compiler/**:
    ```bash
    cd /path/to/compiler
    ```
   
2. **Create a build directory** (recommended):
    ```bash
    mkdir build && cd build
    ```
   
3. **Run CMake**:
    ```bash
    cmake ..
    ```
   
4. **Build the project**:
    ```bash
    make
    ```

5. **Run henlo compiler** on the `.henlo` file:
    ```bash
    ./HenloCompiler ../<file>.henlo
    ```

