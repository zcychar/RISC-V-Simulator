#include "instruction.h"

#include "RoB.h"
#include "decoder.h"
#include "memory.h"

void sjtu::IU::evaluate(RoB &rob, decoder &decoder, MU &mu) {
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
    pc_next = rob.pc;
  } else if (decoder.set_pc) {
    pc_next = decoder.pc;
  } else {
    pc_next = pc + 4;
  }

  u_int32_t raw_inst ;
};
