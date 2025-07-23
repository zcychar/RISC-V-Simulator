#pragma once
#include <array>
#include <istream>

#include "common.h"
namespace sjtu {
class memory {
 public:
  void init(std::istream &in);
  unsigned char load_byte(unsigned int addr) const;
  unsigned short load_half(unsigned int addr) const;
  unsigned int load_word(unsigned int addr) const;
  void store_byte(unsigned int addr,unsigned char val);
  void store_half(unsigned int addr,unsigned short val);
  void store_word(unsigned int addr,unsigned int val);

 private:
  std::array<unsigned char, 128 * PAGE_SIZE> pages = {};
};
}  // namespace sjtu