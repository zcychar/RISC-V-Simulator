#pragma once

/**
 *Instruction unit receives the next PC from decoder and rob to decide what next
 *PC should be, then it reads a raw instruction from memory and when decoder is
 *available, it sends the instruction to decoder.
 *For the situation where decoder is not available at the moment, the unit stalls
 *all its operation in this cycle  and retries to send the same instruction next cycle.
 *The rob's change next pc command is prior to decoder's, since if rob decides a
 *PC, that means we should revert to previous branch address and undo current instruction.
 *
 */

#include "common.h"

namespace sjtu {
class Decoder;
class RoB;
class MU;
class memory;

class IU {
 public:
  IU():ready(false){}

  void evaluate(RoB &rob, Decoder &decoder, memory &mem);

  void revert() {
    std::cerr<<"IU is called to revert this cycle\n";
    PC_next = PC;
    inst_next = inst;
    stall_next = stall;
    ready_next = ready;
    revert_cond_ = true;
  }

  void update() {
    PC = PC_next;
    inst = inst_next;
    stall = stall_next;
    ready = ready_next;
    revert_cond_ = false;
    ready_next = false;
  };

  DecodedInst inst{};
  bool stall = false;
  bool ready = false;
  u_int32_t PC = 0;

 private:
  DecodedInst inst_next{};
  bool stall_next = false;
  bool ready_next = false;
  u_int32_t PC_next = 0;
  bool revert_cond_ = false;
};
}  // namespace sjtu