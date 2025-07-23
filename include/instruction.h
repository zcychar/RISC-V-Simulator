#pragma once
#include <memory.h>

namespace sjtu {

struct DecodedInst {
  INST inst;
  unsigned int rs1,rs2;
  unsigned int rd,imm;
};

class IU {
public:

private:

  memory* mem=nullptr;

  unsigned int addr=0;

  unsigned int addr_next=0;


};
}  // namespace sjtu