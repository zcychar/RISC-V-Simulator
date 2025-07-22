#pragma once
#include <array>

#include "common.h"

namespace sjtu {
struct RSEntry {
  INST inst;
};

class RS {
  void evaluate();

  void update();

 public:
  std::array<RSEntry, 16> list = {};

 private:
  std::array<RSEntry, 16> list_next = {};
};
}  // namespace sjtu
