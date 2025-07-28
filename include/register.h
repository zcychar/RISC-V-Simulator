#pragma once
#include <sys/types.h>

#include <array>

#include "RoB.h"

namespace sjtu {

struct RegEntry {};
class REG {
 public:
  void evaluate(RoB &rob) {
    if (rob.reset) {
      q_next.fill(0);
      b_next.fill(false);
    }
  }

  void set_busy(u_int32_t id, u_int32_t rod_id) {
    q_next[id] = rod_id;
    b_next[id] = true;
    incycle_written[id]=true;
  }
  void set_val(u_int32_t id, u_int32_t val, u_int32_t rob_id) {
    r_next[id] = val;
    if (!incycle_written[id]&&b[id] && q[id] == rob_id) {
      b_next[id] = false;
      q_next[id] = 0;
    }
  }

  u_int32_t operator[](u_int32_t x) const { return r[x]; }

  void update() {
    b_next[0] = false;
    q_next[0] = 0;
    r_next[0] = 0;
    r = r_next;
    b = b_next;
    q = q_next;
    incycle_written.fill(false);
  }

  std::array<u_int32_t, 32> r{};
  std::array<u_int32_t, 32> q{};
  std::array<bool, 32> b{};

 private:
  std::array<u_int32_t, 32> r_next{};
  std::array<u_int32_t, 32> q_next{};
  std::array<bool, 32> b_next{};
  std::array<bool,32>incycle_written{};
};
}  // namespace sjtu