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
  double GetEpsilon() const {
    return epsilon_;
  }
  int GetMaxStep() const {
    return maxstep_;
  }
  void SetEpsilon(double value) {
    if (value < kMinEpsilon) {
      value = kMinEpsilon;
    } else if (value > kMaxEpsilon) {
      value = kMaxEpsilon;
    }
    epsilon_ = value;
  }
  void SetMaxStep(int value) {
    if (value < kMinMaxStep) {
      value = kMinMaxStep;
    } else if (value > kMaxMaxStep) {
      value = kMaxMaxStep;
    }
    maxstep_ = value;
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
