#include "common.h"

namespace sjtu {
class Predictor {
 public:
  bool predict(u_int32_t x) {
    total_count++;
    return true;
  }

  void is_right(u_int32_t x) {
    right_count++;
    return;
  }

  void is_wrong(u_int32_t x) { return; }

  u_int32_t total_count = 0;
  u_int32_t right_count = 0;
};
}  // namespace sjtu
