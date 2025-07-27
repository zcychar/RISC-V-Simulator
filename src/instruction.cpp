#include "instruction.h"

#include "RoB.h"
#include "decoder.h"
#include "memory.h"

void sjtu::IU::evaluate(RoB &rob, Decoder &decoder, memory &mem) {
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
  u_int32_t instr=mem.load_word(PC_next);
  inst_next=decoder.decode(instr);


  u_int32_t raw_inst ;
};
