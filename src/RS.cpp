#include "../include/RS.h"

#include "../include/ALU.h"
#include "../include/LSB.h"
#include "../include/RoB.h"
#include "../include/memory.h"

void sjtu::RS::evaluate(RoB &rob, LSB &lsb) {
  if (rob.reset) {
    for (int i = 0; i < 16; ++i) {
      list_next[i].busy = false;
    }
    alu->load(null, 0, 0, 0);
    return;
  }
  for (int i = 0; i < 16; ++i) {
    if (!list[i].busy) continue;
    if (alu->ready) {
      if (list[i].Dj && list[i].Qj == alu->rob_id) {
        list_next[i].Dj = false;
        list_next[i].Qj = 0;
        list_next[i].Vj = alu->value;
      }
      if (list[i].Dk && list[i].Qk == alu->rob_id) {
        list_next[i].Dk = false;
        list_next[i].Qk = 0;
        list_next[i].Vk = alu->value;
      }
    }
    if (lsb.mu->ready) {
      if (list[i].Dj && list[i].Qj == lsb.mu->rob_id) {
        list_next[i].Dj = false;
        list_next[i].Qj = 0;
        list_next[i].Vj = lsb.mu->value;
      }
      if (list[i].Dk && list[i].Qk == lsb.mu->rob_id) {
        list_next[i].Dk = false;
        list_next[i].Qk = 0;
        list_next[i].Vk = lsb.mu->value;
      }
    }
  }
  for (int i = 0; i < 16; ++i) {
    if (list[i].busy) {
      if (!list_next[i].Dj && !list_next[i].Dk) {
        alu->load(list_next[i].inst, list_next[i].Vj, list_next[i].Vk, list_next[i].dest);
        list_next[i].busy = false;
        return;
      }
    }
  }
}
