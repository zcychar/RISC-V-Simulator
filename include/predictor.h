#include "common.h"

namespace sjtu {

class Predictor {
 public:
  virtual ~Predictor() = default;
  virtual bool predict(u_int32_t x) { return true; };

  void is_right(u_int32_t x) {
    right_count++;
    total_count++;
  }

  void is_wrong(u_int32_t x) { total_count++; }

  virtual void is_branch(u_int32_t x) {}

  virtual void not_branch(u_int32_t x) {}

  u_int32_t total_count = 0;
  u_int32_t right_count = 0;
};

struct Static_Predictor : Predictor {
  bool predict(u_int32_t x) override { return true; };
  void is_branch(u_int32_t x) override {};
  void not_branch(u_int32_t x) override {};
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
    if (GHT[history] >= 2) return true;
    return false;
  };
  void is_branch(u_int32_t x) override {
    GHT[history] = GHT[history] + (GHT[history] != 3);
    history = (history << 1 | 1) & 0xFF;
  }
  void not_branch(u_int32_t x) override {
    GHT[history] = GHT[history] - (GHT[history] != 0);
    history = (history << 1) & 0xFF;
  }
  std::array<u_char, 256> GHT{};
  u_int32_t history = 0;
};

struct gshare_Predictor : Predictor {
  gshare_Predictor() { GHT.fill(2); }

  bool predict(u_int32_t x) override {
    if (total_count < 12) {
      return true;
    }
    u_int32_t tmp = ((x >> 2) & 0x3FF) ^ history;
    if (GHT[tmp] >= 2) return true;
    return false;
  };
  void is_branch(u_int32_t x) override {
    if (total_count >= 11) {
      u_int32_t tmp = ((x >> 2) & 0x3FF) ^ history;
      GHT[tmp] = GHT[tmp] + (GHT[tmp] != 3);
    }
    history = (history << 1 | 1) & 0x3FF;
  }
  void not_branch(u_int32_t x) override {
    if (total_count >= 11) {
      u_int32_t tmp = ((x >> 2) & 0x3FF) ^ history;
      GHT[tmp] = GHT[tmp] - (GHT[tmp] != 0);
    }
    history = (history << 1) & 0x3FF;
  }
  std::array<u_char, 4096> GHT{};
  u_int32_t history = 0;
};

struct tournament_Predictor : Predictor {
  tournament_Predictor() { CPHT.fill(2); }

  bool predict(u_int32_t x) override {
    if (CPHT[hash(x)] >= 2) return local.predict(x);
    return global.predict(x);
  };

  void is_branch(u_int32_t x) override {
    if (!global.predict(x) && local.predict(x)) {
      CPHT[hash(x)] = CPHT[hash(x)] + (CPHT[hash(x)] != 3);
    } else if (global.predict(x) && !local.predict(x)) {
      CPHT[hash(x)] = CPHT[hash(x)] - (CPHT[hash(x)] != 0);
    }
    local.is_branch(x);
    global.is_branch(x);
  }
  void not_branch(u_int32_t x) override {
    if (!global.predict(x) && local.predict(x)) {
      CPHT[hash(x)] = CPHT[hash(x)] - (CPHT[hash(x)] != 0);
    } else if (global.predict(x) && !local.predict(x)) {
      CPHT[hash(x)] = CPHT[hash(x)] + (CPHT[hash(x)] != 3);
    }
    local.not_branch(x);
    global.not_branch(x);
  }
  u_int32_t hash(u_int32_t x) { return ((x >> 2) ^ (x >> 14) ^ (x >> 26)) & 0xFFF; }
  two_bit_Predictor local;
  global_Predictor global;
  std::array<u_char, 4096> CPHT{};
};

}  // namespace sjtu
