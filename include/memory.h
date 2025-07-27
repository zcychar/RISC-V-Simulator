#pragma once
#include <array>
#include <istream>

#include "common.h"

/**
 *The MU structure is designed to deal with load_store instruction, it functions
 *almost the identical way as ALU. For each cycle, it first calculate how much
 *time does the current instruction has to last. If it's reduced to zero then
 *this unit performs the corresponding operation to real memory. Set the value if
 *it's an load instruction and reset the ready sign to true to indicate this unit
 *is ready to give results and receive a new instruction.
 */

namespace sjtu {
  class memory {
  public:
    void init(std::istream &in);

    unsigned char load_byte(u_int32_t addr) const;

    unsigned short load_half(u_int32_t addr) const;

    u_int32_t load_word(u_int32_t addr) const;

    void store_byte(u_int32_t addr, unsigned char val);

    void store_half(u_int32_t addr, unsigned short val);

    void store_word(u_int32_t addr, u_int32_t val);

  private:
    std::array<unsigned char, 128 * PAGE_SIZE> pages = {};
  };

  class RoB;

  class MU {
  public:
    MU() {
      ready_next=true;
    }
    void evaluate(memory &mem, RoB &rob);

    void load(u_int32_t addr, u_int32_t rob_id,u_int32_t value, INST inst);

    void update() {
      remain = remain_next;
      addr = addr_next;
      value = value_next;
      type = type_next;
      rob_id = rob_id_next;
      ready = ready_next;
      ready_next=false;
    };

    u_int32_t remain = 0;
    u_int32_t addr = 0;
    u_int32_t value = 0;
    INST type{};
    u_int32_t rob_id = 0;
    bool ready = false;

  private:
    u_int32_t remain_next = 0;
    u_int32_t addr_next = 0;
    u_int32_t value_next = 0;
    INST type_next{};
    u_int32_t rob_id_next = 0;
    bool ready_next = false;
  };
} // namespace sjtu
