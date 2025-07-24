#pragma once
#include <memory.h>

namespace sjtu {

struct DecodedInst {
  INST inst;
  u_int32_t rs1, rs2;
  u_int32_t rd, imm;
};

class IU {
 public:
  void evaluate();

  void update();

  u_int32_t pc;

  DecodedInst inst;

  bool stall;

  bool ready;

 private:
  u_int32_t pc_next = 0;

  DecodedInst inst_next{};

  bool stall_ready = 0;

  bool ready_next = 0;
};
}  // namespace sjtu