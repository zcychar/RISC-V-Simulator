#pragma once
#include "common.h"
/**
 * The ALU unit is used to do the calculation. Since in this alu all calculation
 * only needs one cycle to be dealt.ALU is ready to receive new instruction in
 * every cycle and the result will be displayed in the very next cycle.
 */
namespace sjtu {

class ALU {
 public:
  ALU():ready_next(true){}

  void load(INST inst, u_int32_t in1, u_int32_t in2, u_int32_t rob_id) {
    inst_next = inst;
    in1_next = in1;
    in2_next = in2;
    ready_next = (inst != null);
    rob_id_next = rob_id;
  }

  void evaluate(){};

  u_int32_t cal() const {
    switch (inst) {
      case addi:
      case add:
        return in1 + in2;
      case sub:
        return in1 - in2;
      case andi:
      case and_:
        return in1 & in2;
      case ori:
      case or_:
        return in1 | in2;
      case xori:
      case xor_:
        return in1 ^ in2;
      case slli:
      case sll:
        return in1 << in2 & 0x1F;
      case srli:
      case srl:
        return in1 >> in2 & 0x1F;
      case srai:
      case sra:
        return static_cast<int32_t>(in1) >> static_cast<int32_t>(in2) & 0x1F;
      case slti:
      case slt:
        return static_cast<int32_t>(in1) < static_cast<int32_t>(in2) ? 1 : 0;
      case sltiu:
      case sltu:
        return in1 < in2 ? 1 : 0;
      case beq:
        return in1 == in2;
      case bge:
        return static_cast<int32_t>(in1) >= static_cast<int32_t>(in2);
      case bgeu:
        return in1 >= in2;
      case blt:
        return static_cast<int32_t>(in1) < static_cast<int32_t>(in2);
      case bltu:
        return in1 < in2;
      case bne:
        return in1 != in2;
      default:
        return 0;
    }
  }

  void update() {
    ready = ready_next;
    ready_next = false;
    inst = inst_next;
    in1 = in1_next;
    in2 = in2_next;
    rob_id = rob_id_next;
    value = cal();
  }

  bool ready = false;
  INST inst{};
  u_int32_t in1 = 0, in2 = 0;
  u_int32_t rob_id = 0;
  u_int32_t value = 0;

 private:
  bool ready_next = false;
  INST inst_next{};
  u_int32_t in1_next = 0, in2_next = 0;
  u_int32_t rob_id_next = 0;
  u_int32_t value_next = 0;
};
}  // namespace sjtu