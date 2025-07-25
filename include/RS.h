#pragma once

#include "common.h"

namespace sjtu {

class RS {
 public:
  void evaluate() {

  };

  void update() {
    list=list_next;
  }

  bool full() {
    for (int i = 0; i < 16; ++i) {
      if (list[i].busy == false) {
        return false;
      }
    }
    return true;
  }

  void push(RSEntry x) {
    for (int i = 0; i < 16; ++i) {
      if (list_next[i].busy == false) {
        list_next[i] = x;
        return;
      }
    }
    throw std::runtime_error("Trying to add into a full list!");
  }

  std::array<RSEntry, 16> list = {};

 private:
  std::array<RSEntry, 16> list_next = {};
};
}  // namespace sjtu
