#pragma once
#include <RoB.h>

#include "common.h"

namespace sjtu {
  class RS;
  class RoB;
  class MU;

  struct LSBEntry {
    bool busy;
    bool wait;
    INST inst;
    u_int32_t Vj, Vk, Qj, Qk;
    u_int32_t dest;
    u_int32_t imm;
    bool Dj, Dk;
  };

  class LSB {
  public:
    LSB(MU *mu): mu(mu) {
    }

    bool full() {
      for (int i = 0; i < 16; ++i) {
        if (list[i].busy == false) {
          return false;
        }
      }
      return true;
    }

    void load(LSBEntry x) {
      for (int i = 0; i < 16; ++i) {
        if (list_next[i].busy == false) {
          list_next[i] = x;
          return;
        }
      }
      throw std::runtime_error("Trying to add into a full list!");
    }

    void evaluate(RS &rs, RoB &rob);

    void update() {
      list = list_next;
    }

    List<LSBEntry> list{};
    MU *mu = nullptr;

  private:
    List<LSBEntry> list_next{};
  };
} // namespace sjtu
