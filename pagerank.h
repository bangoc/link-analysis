#ifndef PAGERANK_H_
#define PAGERANK_H_

#include "base.h"

void PageRank(PageRankInput& inp,
              std::vector<std::pair<int, double>>& out,
              json& debug,
              bool is_debug = false);

#endif  // PAGERANK_H_