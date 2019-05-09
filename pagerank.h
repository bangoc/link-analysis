#ifndef PAGERANK_H_
#define PAGERANK_H_

#include <map>
#include <vector>
#include <Eigen/Dense>

using Eigen::MatrixXd;

void PageRank(double alpha,
              std::vector<int>& vertices,
              std::vector<std::pair<int, int>>& edges,
              double epsilon,
              const int maxstep,
              std::vector<std::pair<int, double>>& out);

#endif  // PAGERANK_H_