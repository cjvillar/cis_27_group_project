# Makefile builds parser_test
# usage: make or make clean to revert

CXX = clang++         # compiler
CXXFLAGS = -std=c++17  # flags
SRCS = parser_test.cpp Parser.cpp Lexer.cpp # source files
TARGET = parser_test # executable name

all: $(TARGET)

# link
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# clean
clean:
	rm -f $(TARGET)

.PHONY: all clean