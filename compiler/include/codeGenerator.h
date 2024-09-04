#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "config.h"


class CodeGenerator {
 public:
  std::string generate(const std::vector<IRInstruction>& ir);
};


#endif //CODEGENERATOR_H