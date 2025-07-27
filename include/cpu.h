#pragma once
#include <ALU.h>
#include <LSB.h>
#include <RS.h>
#include <RoB.h>
#include <decoder.h>
#include <instruction.h>
#include <memory.h>
#include <register.h>

namespace sjtu {
class CPU {
 public:
  CPU() {
    rob = new RoB;
    iu = new IU;
    mem = new memory;
    mu = new MU;
    alu = new ALU;
    lsb = new LSB(mu);
    rs = new RS(alu);
    reg = new REG;
    decoder = new Decoder;
    predictor = new Predictor;
  }

  void init_input(std::istream &in) { mem->init(in); }

  void work() {
    u_int32_t clk = 0;
    try {
      while (true) {
        ++clk;
        evaluate();
        update();
      }
    } catch (u_int32_t num) {
      std::cout << num << std::endl;
    } catch (...) {
      throw;
    }
  }

  void evaluate() {
    alu->evaluate();
    mu->evaluate(*mem, *rob);
    rs->evaluate(*rob, *lsb);
    lsb->evaluate(*rs, *rob);
    decoder->evaluate(*rs, *lsb, *iu, *rob, *reg, *predictor);
    iu->evaluate(*rob, *decoder, *mem);
    reg->evaluate(*rob);
    rob->evaluate(*reg, *rs, *lsb, *predictor);
  }

  void update() {
    alu->update();
    mu->update();
    rs->update();
    lsb->update();
    decoder->update();
    iu->update();
    reg->update();
    rob->update();
  }

 private:
  RoB *rob;
  IU *iu;
  memory *mem;
  MU *mu;
  ALU *alu;
  LSB *lsb;
  RS *rs;
  REG *reg;
  Decoder *decoder;
  Predictor *predictor;
};
}  // namespace sjtu
