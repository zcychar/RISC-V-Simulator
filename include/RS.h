#pragma once

#include "common.h"


namespace sjtu {
  class LSB;
  class RoB;
  class alu;

  class RS {
  public:
    RS(alu* alu):alu(alu){}

    void evaluate(RoB &rob, LSB &lsb);

    void update() {
      list = list_next;
    }

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
          return;
        }
      }
      throw std::runtime_error("Trying to add into a full list!");
    }

    std::array<RSEntry, 16> list = {};
    bool ready = false;
    u_int32_t value = 0;
    u_int32_t rob_id = 0;
    alu* alu=nullptr;

  private:
    std::array<RSEntry, 16> list_next = {};
    bool ready_next = false;
    u_int32_t value_next = 0;
    u_int32_t rob_id_next = 0;
  };
} // namespace sjtu
