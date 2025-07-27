#pragma once

#include <iostream>

#include "common.h"

/**
 *Reorder buffer is the only unit that interacts with real register table.
 *For each instruction, it will be sent to both execution unit (LSB/RS) and RoB
 *and RoB will assign an artifical id to the destnation register. In each cycle,
 *RoB first updates its table by the information from LSB/RS (more specifically,
 *rob reads the information from their calculation unit in the same time with RS/LSB)
 *to update the corresponding value in the table and sets the state done to true
 *to indicate this instruction has been properly executed. Then it detects whether
 *its first instruction is done, if so, it changes the corresponding real register.
 *If the instruction involves branch, it examines whether the branch prediction
 *is correct, if not, rob will set its reset signal to true in the next cycle and
 * notice the instruction unit what's the next PC should be. Every other unit that
 * receives the reset signal will clear what's doing and wait for the correct
 * instructions to come.
 */
namespace sjtu {
class REG;
class RS;
class LSB;
class Predictor;

enum RoBType { toreg, toaddr, tonone, toexit };

struct RoBEntry {
  RoBType type;
  DecodedInst inst;
  bool done;
  u_int32_t dest;
  u_int32_t value;
  u_int32_t addr;
  u_int32_t alt_addr;
};

class RoB {
 public:
  RoB(REG* reg):reg(reg){}

  bool full() { return list.full(); }

  int load(RoBEntry entry);


  void evaluate( RS &rs, LSB &lsb, Predictor &predictor);

  void update() {
    list = list_next;
    reset = reset_next;
    pc = pc_next;
  }

  List<RoBEntry> list{};
  bool reset = false;
  u_int32_t pc = 0;
  REG* reg;

 private:
  List<RoBEntry> list_next{};
  bool reset_next = false;
  u_int32_t pc_next = 0;
};

class Predictor {
 public:
  bool predict(u_int32_t x) { return true; }

  void is_right(u_int32_t x) { return; }

  void is_wrong(u_int32_t x) { return; }
};
}  // namespace sjtu
