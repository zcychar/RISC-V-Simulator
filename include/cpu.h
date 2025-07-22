#pragma once
#include "ALU.h"
#include "instruction.h"
#include "LSB.h"
#include "memory.h"
#include "ROB.h"
#include "RS.h"
#include "register.h"
#include "common.h"

namespace sjtu {
class CPU {
  int work();

  void evaluate();

  void update();

 private:
};
}  // namespace sjtu
