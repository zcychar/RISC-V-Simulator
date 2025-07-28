#include "RoB.h"

#include <ALU.h>
#include <LSB.h>
#include <RS.h>
#include <bits/types/siginfo_t.h>
#include <memory.h>
#include <register.h>

int sjtu::RoB::load(RoBEntry entry) {
  int tmp = list_next.push(entry);
  reg->set_busy(entry.dest, tmp);
  // std::cerr << "rob loaded at:" << tmp <<" control reg:"<<entry.dest<< std::endl;
  return tmp;
}

void sjtu::RoB::evaluate(RS &rs, LSB &lsb, Predictor &predictor) {
  if (reset) {
    reset_next = false;
    pc_next = false;
    list_next.clear();
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
        // std::cerr<<"ROB: commit addr:"<<list[list.first].addr<<" clear reg:"<<list[list.first].dest<<"\n";
        reg->set_val(list[list.first].dest, list[list.first].value, list.first);
        break;
      }
      case toaddr: {
        if (list[list.first].value == (list[list.first].alt_addr != list[list.first].addr + 4)) {
          // std::cerr<<"ROB: commit addr:"<<list[list.first].addr<<" wrong prediction change
          // to:"<<list[list.first].alt_addr<<std::endl;
          pc_next = list[list.first].alt_addr;
          reset_next = true;
          predictor.is_wrong(list[list.first].addr);
        } else {
          // std::cerr<<"ROB: commit addr:"<<list[list.first].addr<<" right prediction \n";
          predictor.is_right(list[list.first].addr);
        }
        break;
      }
      case toexit: {
        throw reg->r[10] & 0xFF;
      }
      default:  // std::cerr<<"ROB: commit addr:"<<list[list.first].addr<<" other instruction \n";
        break;
    }
  }
}
