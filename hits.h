#ifndef HITS_H_
#define HITS_H_

#include "base.h"

#include <map>
#include <vector>

void Hits(const HitsInput& inp,
          std::vector<std::pair<int, double>>& hubs,
          std::vector<std::pair<int, double>>& auth,
          json& debug,
          bool is_debug = false);

#endif  // HITS_H_