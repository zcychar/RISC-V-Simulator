#pragma once

namespace sjtu {
enum INST {
  add,
  sub,
  and_,
  or_,
  xir,
  sll,
  srl,
  sra,
  slt,
  sltu,
  addi,
  andi,
  ori,
  xori,
  slli,
  srli,
  srai,
  slti,
  sltiu,
  lb,
  lbu,
  lh,
  lhu,
  lw,
  sb,
  sh,
  sw,
  beq,
  bge,
  bgeu,
  blt,
  bltu,
  bne,
  jal,
  jalr,
  auipc,
  lui,
  ebreak,
  ecall
};

#define PAGE_SIZE 4096
}  // namespace sjtu