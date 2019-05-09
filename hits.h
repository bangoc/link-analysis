#ifndef HITS_H_
#define HITS_H_

#include <map>
#include <vector>
#include <Eigen/Dense>

using Eigen::MatrixXd;

void Hits(std::vector<int>& vertices,
          std::vector<std::pair<int, int>>& edges,
          double epsilon,
          const int maxstep,
          std::vector<std::pair<int, double>>& hubs,
          std::vector<std::pair<int, double>>& auth);

#endif  // HITS_H_