#include "instruction.h"

#include "RoB.h"
#include "decoder.h"
#include "memory.h"

void sjtu::IU::evaluate(RoB &rob, Decoder &decoder, memory &mem) {
  if (revert_cond_) {
    ready_next = true;
    return;
  }
  if (!rob.reset) {
    if (!decoder.ready) {
      ready_next = true;
      return;
    }
    if (stall) {
      ready_next = false;
      stall_next = false;
      return;
    }
  }
  ready_next = true;
  if (rob.reset) {
    PC_next = rob.pc;
  } else if (decoder.set_pc) {
    PC_next = decoder.pc;
  } else {
    PC_next = PC + 4;
  }
  u_int32_t raw_inst = mem.load_word(PC_next);
  inst_next = decoder.decode(raw_inst);
  if (inst_next.inst == jal || inst_next.inst == jalr) {
    stall_next = true;
  }
};
