#pragma once
#include "common.h"


namespace sjtu {

class RS;
class LSB;
class IU;
class RoB;
class REG;

class decoder {
 public:
  DecodedInst decode(int32_t x);

  void evaluate(RS &rs, LSB &lsb, IU &iu, RoB &rob, REG &reg);

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
