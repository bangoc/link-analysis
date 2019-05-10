#ifndef BASE_H_
#define BASE_H_

#include <Eigen/Dense>
#include <nlohmann/json.hpp>

#include <map>
#include <vector>

using json = nlohmann::json;
using Eigen::MatrixXd;

struct PageRankInput {
  double alpha;
  std::vector<int> vertices;
  std::vector<std::pair<int, int>> edges;
  double epsilon;
  int maxstep;
};

struct HitsInput {
  std::vector<int> vertices;
  std::vector<std::pair<int, int>> edges;
  double epsilon;
  int maxstep;
};

#endif  // BASE_H_