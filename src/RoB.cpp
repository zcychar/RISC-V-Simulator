#include "RoB.h"

#include <ALU.h>
#include <LSB.h>
#include <RS.h>
#include <bits/types/siginfo_t.h>
#include <memory.h>
#include <register.h>

void sjtu::RoB::evaluate(REG &reg, RS &rs, LSB &lsb, Predictor &predictor) {
  if (reset) {
    reset_next = false;
    pc_next = false;
    for (int i = 0; i < 16; ++i) {
      list_next[i] = {};
    }
    return;
  }
  reset_next = false;
  if (rs.alu->ready) {
    list_next[rs.alu->rob_id].value = rs.alu->value;
    list_next[rs.alu->rob_id].done = true;
  }
  if (lsb.mu->ready) {
    list_next[lsb.mu->rob_id].value = lsb.mu->value;
    list_next[lsb.mu->rob_id].done = true;
  }
  if (!list.empty() && list[list.first].done) {
    list_next.pop();
    switch (list[list.first].type) {
      case toreg: {
        reg.set_val(list[list.first].dest, list[list.first].value);
        break;
      }
      case toaddr: {
        if (list[list.first].value == (list[list.first].alt_addr != list[list.first].addr + 4)) {
          pc_next = list[list.first].alt_addr;
          reset_next = true;
          predictor.is_wrong(list[list.first].addr);
        } else {
          predictor.is_right(list[list.first].addr);
        }
        break;
      }
      case toexit: {
        throw reg[10]&0xFF;
      }
      default:
        break;
    }
  }
}
