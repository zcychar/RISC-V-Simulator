#pragma once
#include "instruction.h"

namespace sjtu {
class decoder {
 public:
  DecodedInst decode(int32_t x);

  void evaluate();

  void update();

  bool set_pc = false;

  u_int32_t pc = 0;

  bool ready = false;

 private:
  bool set_pc_next = false;

  u_int32_t pc_next = 0;

  bool ready_next = false;
};
}  // namespace sjtu
