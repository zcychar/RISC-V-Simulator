#pragma once
#include <array>
#include <istream>

#include "common.h"
namespace sjtu {

enum MemoryType{};
class memory {
 public:
  void init(std::istream &in);
  unsigned char load_byte(u_int32_t addr) const;
  unsigned short load_half(u_int32_t addr) const;
  u_int32_t load_word(u_int32_t addr) const;
  void store_byte(u_int32_t addr, unsigned char val);
  void store_half(u_int32_t addr, unsigned short val);
  void store_word(u_int32_t addr, u_int32_t val);

 private:
  std::array<unsigned char, 128 * PAGE_SIZE> pages = {};
};

class mu {
 public:
  mu(memory *mem) : mem(mem) {}

  void evaluate();

  void update();

 u_int32_t remain=0;
 u_int32_t addr=0;
 u_int32_t value=0;
 MemoryType type{};
 u_int32_t rob_id=0;

 private:
  memory *mem;

 u_int32_t remain_next=0;
 u_int32_t addr_next=0;
 u_int32_t value_next=0;
 MemoryType type_next{};
 u_int32_t rob_id_next=0;
};
}  // namespace sjtu