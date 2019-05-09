#ifndef PAGERANK_H_
#define PAGERANK_H_

#include "base.h"

#include <map>
#include <vector>

void PageRank(double alpha,
              std::vector<int>& vertices,
              std::vector<std::pair<int, int>>& edges,
              double epsilon,
              const int maxstep,
              std::vector<std::pair<int, double>>& out,
              json& debug,
              bool is_debug = false);

#endif  // PAGERANK_H_