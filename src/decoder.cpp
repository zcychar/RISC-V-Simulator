#include "decoder.h"

sjtu::DecodedInst sjtu::decoder::decode(int32_t x) {
    DecodedInst inst{};
    u_int32_t opcode = x & 0x7F;
    switch (opcode) {
      case 0b0110011: {  // R
        u_int32_t funct = ((x >> 12) & 0x7) << 7 | (x >> 25) & 0x7F;
        inst.rd = (x >> 7) & 0x1F;
        inst.rs1 = (x >> 15) & 0x1F;
        inst.rs2 = (x >> 20) & 0x1F;
        switch (funct) {
          case 0b0000000000: {
            inst.inst = add;
            break;
          }
          case 0b0000100000: {
            inst.inst = sub;
            break;
          }
          case 0b1110000000: {
            inst.inst = and_;
            break;
          }
          case 0b1100000000: {
            inst.inst = or_;
            break;
          }
          case 0b1000000000: {
            inst.inst = xor_;
            break;
          }
          case 0b0010000000: {
            inst.inst = sll;
            break;
          }
          case 0b1010000000: {
            inst.inst = srl;
            break;
          }
          case 0b1010100000: {
            inst.inst = sra;
            break;
          }
          case 0b0100000000: {
            inst.inst = slt;
            break;
          }
          case 0b0110000000: {
            inst.inst = sltu;
            break;
          }
          default: {
            throw std::runtime_error("Invalid instruction");
          }
        }
        break;
      }
      case 0b0010011: {
        u_int32_t funct3 = (x >> 12) & 0x7;
        inst.rd = (x >> 7) & 0x1F;
        inst.rs1 = (x >> 15) & 0x7;
        switch (funct3) {
          case 0b000: {
            inst.inst = addi;
            inst.imm = x >> 20;
            break;
          }
          case 0b111: {
            inst.inst = andi;
            inst.imm = x >> 20;
            break;
          }
          case 0b110: {
            inst.inst = ori;
            inst.imm = x >> 20;
            break;
          }
          case 0b100: {
            inst.inst = xori;
            inst.imm = x >> 20;
            break;
          }
          case 0b001: {
            inst.inst = slli;
            inst.imm = (x >> 20) & 0x1F;
            break;
          }
          case 0b101: {
            u_int32_t funct7 = (x >> 25) & 0x7F;
            inst.imm = (x >> 20) & 0x1F;
            if (funct7 == 0b0000000) {
              inst.inst = srli;
            } else if (funct7 == 0b0100000) {
              inst.inst = srai;
            } else {
              throw std::runtime_error("Invalid instruction");
            }
            break;
          }
          case 0b010: {
            inst.inst = slti;
            inst.imm = x >> 20;
            break;
          }
          case 0b011: {
            inst.inst = sltiu;
            inst.imm = x >> 20;
            break;
          }
          default:
            throw std::runtime_error("Invalid instruction");
        }
        break;
      }
      case 0b0000011: {
        u_int32_t funct3 = (x >> 12) & 0x7;
        inst.rd = (x >> 7) & 0x1F;
        inst.rs1 = (x >> 15) & 0x7;
        inst.imm = x >> 20;
        switch (funct3) {
          case 0b000: {
            inst.inst = lb;
            break;
          }
          case 0b100: {
            inst.inst = lbu;
            break;
          }
          case 0b001: {
            inst.inst = lh;
            break;
          }
          case 0b101: {
            inst.inst = lhu;
            break;
          }
          case 0b010: {
            inst.inst = lw;
            break;
          }
          default:
            throw std::runtime_error("Invalid instruction");
        }
        break;
      }
      case 0b0100011: {
        inst.rs1 = (x >> 15) & 0x1F;
        inst.rs2 = (x >> 20) & 0x1F;
        inst.imm = (x >> 25) << 5 | (x >> 7) & 0x1F;
        u_int32_t funct3 = (x >> 12) & 0x7;
        switch (funct3) {
          case 0b000: {
            inst.inst = sb;
            break;
          }
          case 0b001: {
            inst.inst = sh;
            break;
          }
          case 0b010: {
            inst.inst = sw;
            break;
          }
          default:
            throw std::runtime_error("Invalid instruction");
        }
        break;
      }
      case 0b1100011: {
        inst.rs1 = (x >> 15) & 0x1F;
        inst.rs2 = (x >> 20) & 0x1F;
        u_int32_t imm12 = (x >> 31) & 0x1;
        u_int32_t imm10_5 = (x >> 25) & 0x3F;
        u_int32_t imm4_1 = (x >> 8) & 0xF;
        u_int32_t imm11 = (x >> 7) & 0x1;
        inst.imm = (imm12 << 12) | (imm11 << 11) | (imm10_5 << 5) | (imm4_1 << 1);
        u_int32_t funct3 = (x >> 12) & 0x7;
        switch (funct3) {
          case 0b000: {
            inst.inst = beq;
            break;
          }
          case 0b101: {
            inst.inst = bge;
            break;
          }
          case 0b111: {
            inst.inst = bgeu;
            break;
          }
          case 0b100: {
            inst.inst = blt;
            break;
          }
          case 0b110: {
            inst.inst = bltu;
            break;
          }
          case 0b001: {
            inst.inst = bne;
            break;
          }
          default:
            throw std::runtime_error("Invalid instruction");
        }
        break;
      }
      case 0b1101111: {
        u_int32_t imm20 = (x >> 31) & 0x1;
        u_int32_t imm10_1 = (x >> 21) & 0x3FF;
        u_int32_t imm11 = (x >> 20) & 0x1;
        u_int32_t imm19_12 = (x >> 12) & 0xFF;
        inst.imm = (imm20 << 20) | (imm19_12 << 12) | (imm11 << 11) | (imm10_1 << 1);
        inst.rd = (x >> 7) & 0x1F;
        inst.inst = jal;
        break;
      }
      case 0b1100111: {
        inst.imm = (x >> 20);
        inst.rd = (x >> 7) & 0x1F;
        inst.rs1 = (x >> 15) & 0x1F;
        inst.inst = jalr;
        break;
      }
      case 0b0010111: {
        inst.imm = x & 0xFFFFF000;
        inst.rd = (x >> 7) & 0x1F;
        inst.inst = auipc;
        break;
      }
      case 0b0110111: {
        inst.imm = x & 0xFFFFF000;
        inst.rd = (x >> 7) & 0x1F;
        inst.inst = lui;
        break;
      }
      default:
        throw std::runtime_error("Invalid instruction");
    }
    return inst;
  }