#pragma once

#include "common.h"

/**
 * LoadStore Buffer corresponds to the reserve station for memory-related instruction,
 * but the difference is LSB only support execution of the first instruction in
 * time order. It also updates its dependence every cycle, but only when both
 * first instruction is independent and mu is ready, it sends the instruction to operation.
 */

namespace sjtu {
class RS;
class RoB;
class MU;

struct LSBEntry {
  bool busy;
  INST inst;
  u_int32_t Vj, Vk, Qj, Qk;
  u_int32_t dest;
  u_int32_t imm;
  bool Dj, Dk;
};

class LSB {
 public:
  LSB(MU *mu) : mu(mu) {}

  bool full() {
    for (int i = 0; i < 16; ++i) {
      if (list[i].busy == false) {
        return false;
      }
    }
    return true;
  }

  void load(LSBEntry x) {
    int tmp = list_next.push(x);
    // std::cerr << "LSB:load rob_id:" << x.dest << " into slot:" << tmp<< std::endl;
    return;
    throw std::runtime_error("Trying to add into a full list!");
  }

  void evaluate(RS &rs, RoB &rob);

  void update() { list = list_next; }

  List<LSBEntry> list{};
  MU *mu = nullptr;

 private:
  List<LSBEntry> list_next{};
};
}  // namespace sjtu
