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
  void store_byte(unsigned char val);
  void store_half(unsigned short val);
  void store_word(unsigned int val);

 private:
  std::array<unsigned char, 16 * PAGE_SIZE> pages;
};
}  // namespace sjtu