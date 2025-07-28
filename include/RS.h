#pragma once

#include "common.h"

/**
 * The reserve station serves all the instruction which needs to do calculation,
 * so it will work closely with alu unit. It first updates its instructions'
 * register dependency based on the results of alu and lsb. Then it choosees an
 * instruction which has both independent operation values (if exists) and send
 * to alu for calculation. Since all calculation needs only one cycle, we can
 * free the slot in the next cycle.
 */
namespace sjtu {
class LSB;
class RoB;
class ALU;

class RS {
 public:
  RS(ALU *alu) : alu(alu) {}

  void evaluate(RoB &rob, LSB &lsb);

  void update() { list = list_next; }

  bool full() {
    for (int i = 0; i < 16; ++i) {
      if (list[i].busy == false) {
        return false;
      }
    }
    return true;
  }

  void load(RSEntry x) {
    for (int i = 0; i < 16; ++i) {
      if (list_next[i].busy == false) {
        list_next[i] = x;
        // std::cerr<<"RS: load instruction dependence j:"<<x.Dj<<","<<x.Qj<<" k:"<<x.Dk<<","<<x.Qk<<std::endl;
        return;
      }
    }
    throw std::runtime_error("Trying to add into a full list!");
  }

  std::array<RSEntry, 16> list = {};
  ALU *alu = nullptr;

 private:
  std::array<RSEntry, 16> list_next = {};
};
}  // namespace sjtu
