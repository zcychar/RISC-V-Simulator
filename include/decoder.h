#pragma once
#include "instruction.h"

namespace sjtu {

class decoder {
 public:
  static DecodedInst decode(unsigned int x) {
    DecodedInst inst{};
    unsigned int opcode = x & 0x7F;
    switch (opcode) {
      case 0x33: {
        unsigned int funct = ( (x >> 12) & 0x7)<<7 | (x >> 25) & 0x7F;
        inst.rd=(x>>7)&0x1F;
        inst.rs1=(x>>15)&0x1F;
        inst.rs2=(x>>20)&0x1F;
        switch (funct) {
          case 0b0000000000: {
            inst.inst=add;
            break;
          }
          case 0b0000100000: {
            inst.inst=sub;
            break;
          }
          case 0b1110000000:{
            inst.inst=and_;
            break;
          }
          case 0b1100000000:{
            inst.inst=or_;
            break;
          }
          case 0b1000000000: {
            inst.inst=xor_;
            break;
          }
          case 0b0010000000: {
            inst.inst=sll;
            break;
          }
          case 0b1010000000: {
            inst.inst=srl;
            break;
          }
          case 0b1010100000: {
            inst.inst=sra;
            break;
          }
        }
      }
    }
    return inst;
  }
};
}  // namespace sjtu
