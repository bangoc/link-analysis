#ifndef BASE_H_
#define BASE_H_

#include <Eigen/Dense>
#include <nlohmann/json.hpp>

#include <map>
#include <vector>

using json = nlohmann::json;
using Eigen::MatrixXd;

struct PageRankInput {
  double alpha = 0.75;
  std::vector<int> vertices;
  std::vector<std::pair<int, int>> edges;
  double epsilon = 0.00001;
  int maxstep = 5;
};

struct HitsInput {
  std::vector<int> vertices;
  std::vector<std::pair<int, int>> edges;
  double epsilon;
  int maxstep;
};

#endif  // BASE_H_