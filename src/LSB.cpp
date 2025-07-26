#include "LSB.h"

#include <ALU.h>
#include <memory.h>
#include <RS.h>

void sjtu::LSB::evaluate(RS &rs, RoB &rob) {
  if (rob.reset) {
    for (int i = 0; i < 16; ++i) {
      list_next[i].busy = false;
    }
    mu->load(0, 0, 0, null);
    return;
  }
  for (int i = 0; i < 16; ++i) {
    if (rs.alu->ready && list[i].Dj && list[i].Qj == rs.alu->rob_id) {
      list_next[i].Dj = false;
      list_next[i].Qj = 0;
      list_next[i].Vj = rs.alu->value;
    }
    if (rs.alu->ready && list[i].Dk && list[i].Qk == rs.alu->rob_id) {
      list_next[i].Dk = false;
      list_next[i].Qk = 0;
      list_next[i].Vk = rs.alu->value;
    }
    if (mu->ready && list[i].Dj && list[i].Qj == mu->rob_id) {
      list_next[i].Dj = false;
      list_next[i].Qj = 0;
      list_next[i].Vj = mu->value;
    }
    if (mu->ready && list[i].Dk && list[i].Qk == mu->rob_id) {
      list_next[i].Dk = false;
      list_next[i].Qk = 0;
      list_next[i].Vk = mu->value;
    }
    if (!rob.list.empty()&&list[i].wait && rob.list.first==list[i].dest) {
      list_next[i].wait=false;
    }
  }
}
