#pragma once
#include "common.h"

/**
 *The decoder serves the function of decode and dispatch.
 *it first decides where to put the instruction it received and pre-process,
 *if there's no space to put the instruction , this unit will be unavailable next
 *cycle and retry until it successes.
 *Specifically, it tells instruction unit where to jump to
 *when face with jal or jalr instruction.
 *Considering the instruction unit would be unware of the information this
 *unit provides in the very next cycle. This unit will set a special stall
 *state to instruction unit to mannually stall IU's function in the next term
 *when a jal or jalr instruction is loaded into the decoder.
 */
namespace sjtu {

class RS;
class LSB;
class IU;
class RoB;
class REG;
class Predictor;

class decoder {
 public:
  DecodedInst decode(int32_t x);

  void evaluate(RS &rs, LSB &lsb, IU &iu, RoB &rob, REG &reg, Predictor &predictor);

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
