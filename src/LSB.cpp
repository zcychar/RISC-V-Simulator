#include "../include/LSB.h"

#include "../include/ALU.h"
#include "../include/RS.h"
#include "../include/RoB.h"
#include "../include/memory.h"

void sjtu::LSB::evaluate(RS &rs, RoB &rob) {
  if (rob.reset) {
    list_next.clear();
    mu->load(0, 0, 0, null);
    return;
  }
  for (int i = 0; i < 16; ++i) {
    if (list[i].busy) {
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
    }
  }
  if (mu->remain == 0 && !list.empty()) {
    int index = list.first;
    if (list[index].busy && !list_next[index].Dj && !list_next[index].Dk) {
      ////std::cerr<<"LSB:send robid:"<<list[index].dest<<" to mu calculate\n";
      mu->load(static_cast<int32_t>(list_next[index].Vj + list_next[index].imm), list_next[index].dest,
               list_next[index].Vk, list_next[index].inst);
      list_next[index].busy = false;
      list_next.pop();
    }
  }
}
