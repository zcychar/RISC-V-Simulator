#pragma once
#include "common.h"

namespace sjtu {
enum RobState {};

struct RoBEntry {
  bool busy;
  DecodedInst inst;
  RobState state;
  u_int32_t dest;
  u_int32_t value;
};

class RoB {
 public:
  bool full() { return list.full(); }

  void push(RoBEntry x);

  void evaluate();

  void update();

  List<RoBEntry> list{};

  bool reset = false;

  u_int32_t pc = 0;

 private:
  List<RoBEntry> list_next{};

  bool reset_next = false;

  u_int32_t pc_next = 0;
};
}  // namespace sjtu
