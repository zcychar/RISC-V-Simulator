#include "common.h"

namespace sjtu {

class Predictor {
 public:
  virtual ~Predictor() = default;
  virtual bool predict(u_int32_t x) { return true; };

  void is_right() {
    right_count++;
    total_count++;
  }

  void is_wrong() { total_count++; }

  virtual void is_branch(u_int32_t x) {}

  virtual void not_branch(u_int32_t x) {}

  u_int32_t total_count = 0;
  u_int32_t right_count = 0;
};

struct Static_Predictor : Predictor {
  bool predict(u_int32_t x) override { return true; };
  void is_branch(u_int32_t x) override{};
  void not_branch(u_int32_t x) override{};
};

struct two_bit_Predictor : Predictor {
  two_bit_Predictor() { PHT.fill(2); }

  bool predict(u_int32_t x) override {
    if (PHT[hash(x)] >= 2) return true;
    return false;
  };
  void is_branch(u_int32_t x) override { PHT[hash(x)] = PHT[hash(x)] + (PHT[hash(x)] != 3); };
  void not_branch(u_int32_t x) override { PHT[hash(x)] = PHT[hash(x)] - (PHT[hash(x)] != 0); }

  u_int32_t hash(u_int32_t x) { return ((x >> 2) ^ (x >> 14) ^ (x >> 26)) & 0xFFF; }
  std::array<u_char, 4096> PHT{};
};

struct global_Predictor : Predictor {
  global_Predictor() { GHT.fill(2); }

  bool predict(u_int32_t x) override {
    if (total_count < 4) {
      return true;
    }
    if (GHT[history] >= 2) return true;
    return false;
  };
  void is_branch(u_int32_t x) override {
    GHT[history] = GHT[history] + (GHT[history] != 3);
    history = history << 1 | 1;
  }
  void not_branch(u_int32_t x) override {
    GHT[history] = GHT[history] - (GHT[history] != 0);
    history = history << 1;
  }

  std::array<u_char, 16> GHT{};
  u_char history = 0;
};
}  // namespace sjtu
