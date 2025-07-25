#pragma once
#include <sys/types.h>

#include <array>
#include <stdexcept>

namespace sjtu {


enum INST {
  add,
  sub,
  and_,
  or_,
  xor_,
  sll,
  srl,
  sra,
  slt,
  sltu,
  addi,
  andi,
  ori,
  xori,
  slli,
  srli,
  srai,
  slti,
  sltiu,
  lb,
  lbu,
  lh,
  lhu,
  lw,
  sb,
  sh,
  sw,
  beq,
  bge,
  bgeu,
  blt,
  bltu,
  bne,
  jal,
  jalr,
  auipc,
  lui,
  null,
};

struct DecodedInst {
  INST inst;
  u_int32_t rs1, rs2;
  u_int32_t rd, imm;
};

struct RSEntry {
  bool busy;
  INST inst;
  u_int32_t Vj, Vk, Qj, Qk;
  u_int32_t dest;
  bool Dj, Dk;
};

template <typename T>
struct List {
  List() : first(0), last(0), size(0) {}

  bool full() const { return size == list.size(); }

  bool empty() const { return size == 0; }

  T &operator[](u_int32_t x) { return list[x]; }

  void pop() {
    if (empty()) {
      return;
    }
    first = (first + 1) % list.size();
    --size;
  }

  int push(const T &val) {
    if (full()) {
      return -1;
    }
    list[last] = val;
    last = (last + 1) % list.size();
    ++size;
    return last;
  }

  std::array<T, 16> list{};
  u_int32_t first, last;
  u_int32_t size;
};

#define PAGE_SIZE 4096
}  // namespace sjtu