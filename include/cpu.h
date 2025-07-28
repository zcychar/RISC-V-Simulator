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
    iu = new IU;
    mem = new memory;
    mu = new MU;
    alu = new ALU;
    lsb = new LSB(mu);
    rs = new RS(alu);
    reg = new REG;
    decoder = new Decoder;
    predictor = new Predictor;
    rob = new RoB(reg);
  }

  void init_input(std::istream &in) { mem->init(in); }

  void work() {
    u_int32_t clk = 0;
    try {
      while (true) {
        ++clk;
        std::cerr<<std::endl<<"clock:"<<clk<<std::endl;
        evaluate();
        update();
      }
    } catch (u_int32_t num) {
      std::cout << num << std::endl;
    } catch (std::runtime_error &err) {
      std::cerr << err.what();
    }
  }

  void evaluate() {
    debug_printer();
    alu->evaluate();
    mu->evaluate(*mem, *rob);
    rs->evaluate(*rob, *lsb);
    lsb->evaluate(*rs, *rob);
    decoder->evaluate(*rs, *lsb, *iu, *rob, *reg, *predictor);
    iu->evaluate(*rob, *decoder, *mem);
    reg->evaluate(*rob);
    rob->evaluate(*rs, *lsb, *predictor);

  }

  void debug_printer() {
    std::cerr << "IU ready:" << iu->ready << " PC:" << iu->PC << std::endl;
    std::cerr <<"rob size:"<<rob->list.size<<std::endl;
    // for(int j=0,i=rob->list.first;j<rob->list.size;++j,i=(i+1)%16) {
    //   std::cerr<<"  rob_id:"<<i<<" done:"<<rob->list[i].done<<" addr:"<<rob->list[i].addr<<std::endl;
    // }
    //
    // std::cerr << "alu ready:" << alu->ready << " rob_id:" << alu->rob_id <<" value:"<<alu->value<< std::endl;
    // std::cerr << "mu ready:" << mu->ready << " rob_id:" << mu->rob_id <<" value:"<<mu->value<< std::endl;
    // for(int i=0;i<32;++i) {
    //     std::cerr<<i<<":r:"<<reg->r[i]<<" b:"<<reg->b[i]<<" q:"<<reg->q[i]<<"\t";
    //   if((i+1)%8==0) {
    //     std::cerr<<std::endl;
    //   }
    // }
    // std::cerr<<std::endl;
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
