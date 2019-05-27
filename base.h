#ifndef BASE_H_
#define BASE_H_

#include <Eigen/Dense>
#include <nlohmann/json.hpp>

#include <map>
#include <vector>

using json = nlohmann::json;
using Eigen::MatrixXd;

struct PowerInput {
 public:
  double GetEpsilon() {
    return epsilon_;
  }
  int GetMaxStep() {
    return maxstep_;
  }
  void SetEpsilon(double value) {
    if (epsilon_ < kMinEpsilon) {
      epsilon_ = kMinEpsilon;
    } else if (epsilon_ > kMaxEpsilon) {
      epsilon_ = kMaxEpsilon;
    }
  }
  void SetMaxStep(int value) {
    if (value < kMinMaxStep) {
      maxstep_ = kMinMaxStep;
    } else if (value > kMaxMaxStep) {
      maxstep_ = kMaxMaxStep;
    }
  }
  static constexpr int kMinMaxStep = 1;
  static constexpr int kMaxMaxStep = 1000;
  static constexpr double kMinEpsilon = 1e-10;
  static constexpr double kMaxEpsilon = 1e-3;
 private:
  double epsilon_ = 1e-5 ;
  int maxstep_ = 5;
};

struct PageRankInput: PowerInput {
  double alpha = 0.75;
  std::vector<int> vertices;
  std::vector<std::pair<int, int>> edges;
};

struct HitsInput: PowerInput {
  std::vector<int> vertices;
  std::vector<std::pair<int, int>> edges;
};

#endif  // BASE_H_
