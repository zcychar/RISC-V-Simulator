#include "decoder.h"

#include "LSB.h"
#include "RS.h"
#include "RoB.h"
#include "instruction.h"
#include "register.h"

sjtu::DecodedInst sjtu::decoder::decode(int32_t x) {
  DecodedInst inst{};
  u_int32_t opcode = x & 0x7F;
  switch (opcode) {
    case 0b0110011: {
      // R
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

void sjtu::decoder::evaluate(RS &rs, LSB &lsb, IU &iu, RoB &rob, REG &reg) {
  if (rob.reset) {
    ready_next = true;
    return;
  }
  if (!iu.ready) {
    return;
  }
  if (rob.full()) {
    iu.reset();
    return;
  }
  ready_next = true;
  auto inst = iu.inst;
  switch (inst.inst) {
    case add:
    case sub:
    case sll:
    case slt:
    case sltu:
    case xor_:
    case srl:
    case sra:
    case or_:
    case and_: {
      if (rs.full()) {
        ready_next = false;
        iu.reset();
        return;
      }
      u_int32_t rob_id = rob.push(RoBEntry{inst, false, inst.rd, 0});
      RSEntry entry{true, inst.inst, 0, 0, 0, 0, rob_id, false, false};
      if (reg.b[inst.rs1]) {
        entry.Qj = reg.q[inst.rs1];
        entry.Dj = true;
      } else {
        entry.Vj = reg[inst.rs1];
      }
      if (reg.b[inst.rs2]) {
        entry.Qk = reg.q[inst.rs2];
        entry.Dk = true;
      } else {
        entry.Vk = reg[inst.rs2];
      }
      rs.load(entry);
      return;
    }
    case addi:
    case slli:
    case slti:
    case sltiu:
    case xori:
    case srli:
    case srai:
    case ori:
    case andi: {
      if (rs.full()) {
        ready_next = false;
        iu.reset();
        return;
      }
      u_int32_t rob_id = rob.push(RoBEntry{inst, false, inst.rd, 0});
      RSEntry entry{true, inst.inst, 0, inst.imm, 0, 0, rob_id, false, false};
      if (reg.b[inst.rs1]) {
        entry.Qj = reg.q[inst.rs1];
        entry.Dj = true;
      } else {
        entry.Vj = reg[inst.rs1];
      }
      rs.load(entry);
      return;
    }
    case lb:
    case lh:
    case lw:
    case lbu:
    case lhu: {
      if (lsb.full()) {
        ready_next = false;
        iu.reset();
        return;
      }
      u_int32_t rob_id = rob.push(RoBEntry{inst, false, inst.rd, 0});
      LSBEntry entry{true, false, inst.inst, 0, 0, 0, 0, rob_id, inst.imm, false, false};
      if (reg.b[inst.rs1]) {
        entry.Qj = reg.q[inst.rs1];
        entry.Dj = true;
      } else {
        entry.Vj = reg[inst.rs1];
      }
      lsb.load(entry);
      return;
    }
    case sb:
    case sh:
    case sw: {
      if (lsb.full()) {
        ready_next = false;
        iu.reset();
        return;
      }
      u_int32_t rob_id = rob.push(RoBEntry{inst, false, inst.rd, 0});
      LSBEntry entry{true, false, inst.inst, 0, 0, 0, 0, rob_id, inst.imm, false, false};
      if (reg.b[inst.rs1]) {
        entry.Qj = reg.q[inst.rs1];
        entry.Dj = true;
      } else {
        entry.Vj = reg[inst.rs1];
      }
      if (reg.b[inst.rs2]) {
        entry.Qk = reg.q[inst.rs2];
        entry.Dk = true;
      } else {
        entry.Vk = reg[inst.rs2];
      }
      lsb.load(entry);
      return;
    }
    case beq:
    case bne:
    case blt:
    case bge:
    case bltu:
    case bgeu: {
    }

    case jal: {
    }
    case jalr: {
      if (reg.b[inst.rs1]) {
        ready_next = false;
        iu.reset();
        return;
      }
    }

    case lui:
    case auipc:
    default:
      throw std::runtime_error("Invalid instruction!");
  }
};

void sjtu::decoder::update() {
  set_pc = set_pc_next;
  pc = pc_next;
  ready = ready_next;
  set_pc_next = false;
  ready_next = false;
}
