#include <iostream>

#include "cpu.h"

int main() {
  sjtu::CPU cpu;
  cpu.init_input(std::cin);

  cpu.work();
  return 0;
}