#include "../include/instruction.h"

#include "../include/RoB.h"
#include "../include/decoder.h"
#include "../include/memory.h"

void sjtu::IU::evaluate(RoB &rob, Decoder &decoder, memory &mem) {
  if (revert_cond_) {
    return;
  }
  if (!rob.reset) {
    if (stall) {
      // std::cerr << "IU:Stalled\n";
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
  // std::cerr << std::hex << "IU:reads at PC:" << PC_next << " raw_inst:" << raw_inst << std::endl;
  inst_next = decoder.decode(raw_inst);
  if (inst_next.inst == jal || inst_next.inst == jalr || inst_next.inst == beq || inst_next.inst == bne ||
      inst_next.inst == blt || inst_next.inst == bge || inst_next.inst == bltu || inst_next.inst == bgeu) {
    // std::cerr << "IU:sets stall in next cycle\n";
    stall_next = true;
  }
};
