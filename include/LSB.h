#pragma once


namespace sjtu {

struct LSBEntry {

};
class LSB {
public:

  bool full() {
    return list.full();
  }
  void evaluate();

  void update();
  List<LSBEntry>list{};
private:
  List<LSBEntry>list_next{};
};
}