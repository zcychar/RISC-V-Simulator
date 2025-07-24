#pragma once

namespace sjtu {

struct RegEntry{};
class reg{
public:


  std::array<u_int32_t,32>r{};

  std::array<u_int32_t,32>d{};

private:
  std::array<u_int32_t,32>r_next{};
};
}