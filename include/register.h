#pragma once

namespace sjtu {

struct RegEntry {};
class reg {
 public:
  void evaluate();

  void update() {
    r = r_next;
    d = d_next;
  }

  std::array<u_int32_t, 32> r{};

  std::array<u_int32_t, 32> d{};

 private:
  std::array<u_int32_t, 32> r_next{};

  std::array<u_int32_t, 32> d_next{};
};
}  // namespace sjtu