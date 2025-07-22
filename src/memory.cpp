#include "memory.h"
#include <sstream>

void sjtu::memory::init(std::istream &in) {
  std::string str;
  int addr = 0;
  while (getline(in, str)) {
    if (str.empty()) continue;
    if (str[0] == '@') {
      addr = std::stoi(str.data() + 1, nullptr, 16);
      continue;
    }
    std::istringstream line(str);
    line >> std::hex;
    unsigned int tmp = 0, cnt = 0, cur = 0;
    while (!line.eof()) {
      line >> cur;
      tmp |= cur << ((cnt++) * 8);
      if (cnt == 4) {
        store_byte(addr, tmp);
        addr += 4;
        tmp = cnt = cur = 0;
      }
    }
  }
}

unsigned char sjtu::memory::load_byte(unsigned int addr) const {
  return *reinterpret_cast<unsigned char const *>(pages.data()+addr);
}
unsigned short sjtu::memory::load_half(unsigned int addr) const {
  return *reinterpret_cast<unsigned short const *>(pages.data()+addr);
}
unsigned int sjtu::memory::load_word(unsigned int addr) const {
  return *reinterpret_cast<unsigned int const *>(pages.data()+addr);
}
void sjtu::memory::store_byte(unsigned int addr, unsigned char val) {
  *reinterpret_cast<unsigned char *>(pages.data()+addr)=val;
}
void sjtu::memory::store_half(unsigned int addr, unsigned short val) {
  *reinterpret_cast<unsigned short *>(pages.data()+addr)=val;
}
void sjtu::memory::store_word(unsigned int addr, unsigned int val) {
  *reinterpret_cast<unsigned int *>(pages.data()+addr)=val;
}
