#pragma once
#include "common.h"

namespace sjtu {

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
  bool full() {
    for (int i = 0; i < 16; ++i) {
      if (list[i].busy == false) {
        return false;
      }
    }
    return true;
  }

  void push(LSBEntry x) {
    for (int i = 0; i < 16; ++i) {
      if (list_next[i].busy == false) {
        list_next[i] = x;
        return;
      }
    }
    throw std::runtime_error("Trying to add into a full list!");
  }

  void evaluate();

  void update() {
    list = list_next;
    load_ready = load_ready_next;
    rob_id = rob_id_next;
    value = value_next;
    rob_id_next = 0;
    load_ready_next = false;
  }

  List<LSBEntry> list{};
  bool load_ready = false;
  u_int32_t rob_id = 0;
  u_int32_t value = 0;

 private:
  List<LSBEntry> list_next{};
  bool load_ready_next = false;
  u_int32_t rob_id_next = 0;
  u_int32_t value_next = 0;
};
}  // namespace sjtu