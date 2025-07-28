#include "memory.h"

#include <RoB.h>

#include <iostream>
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
    u_int32_t tmp = 0, cnt = 0, cur = 0;
    while (!line.eof()) {
      line >> cur;
      tmp |= cur << ((cnt++) * 8);
      if (cnt == 4) {
        store_word(addr, tmp);
        addr += 4;
        tmp = cnt = cur = 0;
      }
    }
  }
}

unsigned char sjtu::memory::load_byte(u_int32_t addr) const {
  if (!pages.count(addr / PAGE_SIZE)) return 0;
  return *reinterpret_cast<unsigned char const *>(pages.at(addr / PAGE_SIZE).data() + addr % PAGE_SIZE);
}

unsigned short sjtu::memory::load_half(u_int32_t addr) const {
  if (!pages.count(addr / PAGE_SIZE)) return 0;
  return *reinterpret_cast<unsigned short const *>(pages.at(addr / PAGE_SIZE).data() + addr % PAGE_SIZE);
}

u_int32_t sjtu::memory::load_word(u_int32_t addr) const {
  if (!pages.count(addr / PAGE_SIZE)) return 0;
  return *reinterpret_cast<u_int32_t const *>(pages.at(addr / PAGE_SIZE).data() + addr % PAGE_SIZE);
}

void sjtu::memory::store_byte(u_int32_t addr, unsigned char val) {
  *reinterpret_cast<unsigned char *>(pages[addr / PAGE_SIZE].data() + addr % PAGE_SIZE) = val;
}

void sjtu::memory::store_half(u_int32_t addr, unsigned short val) {
  *reinterpret_cast<unsigned short *>(pages[addr / PAGE_SIZE].data() + addr % PAGE_SIZE) = val;
}

void sjtu::memory::store_word(u_int32_t addr, u_int32_t val) {
  // std::cerr << "store word :" << val << " into :" << addr << std::endl;
  *reinterpret_cast<u_int32_t *>(pages[addr / PAGE_SIZE].data() + addr % PAGE_SIZE) = val;
}

void sjtu::MU::load(u_int32_t addr, u_int32_t rob_id, u_int32_t value, INST inst) {
  // std::cerr << "MU: load an instruction at robid:" << rob_id << " \n";
  remain_next = 3;
  addr_next = addr;
  rob_id_next = rob_id;
  type_next = inst;
  value_next = value;
  ready_next = false;
}

void sjtu::MU::evaluate(memory &mem, RoB &rob) {
  if (rob.reset) {
    ready_next = false;
    remain_next = 0;
    addr_next = 0;
    rob_id_next = 0;
    value_next = 0;
    type_next = null;
    return;
  }
  ready_next = false;
  if (remain > 0) {
    remain_next = remain - 1;
    if (remain_next == 0 && type != null) {
      // std::cerr << "MU:instruction at " << rob_id << " is completed, value\n";
      ready_next = true;
      switch (type) {
        case lb: {
          value_next = static_cast<int32_t>(mem.load_byte(addr_next));
          break;
        }
        case lbu: {
          value_next = mem.load_byte(addr_next);
          break;
        }
        case lh: {
          value_next = static_cast<int32_t>(mem.load_half(addr_next));
          break;
        }
        case lhu: {
          value_next = mem.load_half(addr_next);
          break;
        }
        case lw: {
          value_next = mem.load_word(addr_next);
          break;
        }
        case sb: {
          mem.store_byte(addr_next, value_next & 0x1);
          break;
        }
        case sh: {
          mem.store_half(addr_next, value_next & 0xFF);
          break;
        }
        case sw: {
          mem.store_word(addr_next, value_next);
          break;
        }
        default:
          throw std::runtime_error("mu meets invalid instruction");
      }
    }
  }
}
