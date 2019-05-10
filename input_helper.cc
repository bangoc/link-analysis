#include "input_helper.h"

#include <fstream>

namespace {

void ParseGraph(std::ifstream& inp,
    std::vector<int>& vertices,
    std::vector<std::pair<int, int>>& edges) {
  int n = 0;
  inp >> n;
  for (int i = 0; i < n; ++i) {
    int v;
    inp >> v;
    vertices.push_back(v);
  }
  int m = 0;
  inp >> m;
  for (int i = 0; i < m; ++i) {
    int b, e;
    inp >> b >> e;
    edges.push_back(std::make_pair(b, e));
  }
}

}  // namespace


void ParsePageRankInput(PageRankInput& params,
                        const std::string& fname) {
  std::ifstream inp{fname};
  inp >> params.alpha;
  ParseGraph(inp, params.vertices, params.edges);
  inp >> params.epsilon >> params.maxstep;
}

void ParseHitsInput(HitsInput& params,
                    const std::string& fname) {
  std::ifstream inp{fname};
  ParseGraph(inp, params.vertices, params.edges);
  inp >> params.epsilon >> params.maxstep;
}
