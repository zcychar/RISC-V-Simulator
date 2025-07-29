#include <iostream>

#include "../include/cpu.h"

int main(int argc, char* argv[]) {
  sjtu::CPU cpu(argc, argv);
  cpu.init_input(std::cin);
  cpu.work();
  return 0;
}