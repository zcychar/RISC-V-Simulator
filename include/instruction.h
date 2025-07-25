#pragma once

#include <memory.h>

#include "common.h"

namespace sjtu {
class decoder;
class RoB;
class MU;

class IU {
 public:
  void evaluate(RoB &rob, decoder &decoder, MU &mu);

  void reset() { stall_next = true; }

  void update() {
    pc = pc_next;
    inst = inst_next;
    stall = stall_next;
    ready = ready_next;
  };

  u_int32_t pc = 0;
  DecodedInst inst{};
  bool stall = false;
  bool ready = false;
  u_int32_t addr = 0;

 private:
  u_int32_t pc_next = 0;
  DecodedInst inst_next{};
  bool stall_next = false;
  bool ready_next = false;
  u_int32_t addr_next = 0;
};
}  // namespace sjtu