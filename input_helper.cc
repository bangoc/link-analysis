#include "input_helper.h"

#include "glog/logging.h"
#include <fstream>

namespace {

void ParseGraph(std::istream& inp,
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

void ParsePowerInput(PowerInput& params, std::istream& inp) {
  double epsilon;
  int maxstep;
  inp >> epsilon >> maxstep;
  params.SetEpsilon(epsilon);
  params.SetMaxStep(maxstep);
}

}  // namespace

void ParsePageRankParams(PageRankInput& params,
                        std::istream& inp) {
  inp >> params.alpha;
  ParseGraph(inp, params.vertices, params.edges);
  ParsePowerInput(params, inp);
}

void ParsePageRankInput(PageRankInput& params,
                        const std::string& fname) {
  std::ifstream inp{fname};
  ParsePageRankParams(params, inp);
}

void ParseHitsParams(HitsInput& params,
                     std::istream& inp) {
  ParseGraph(inp, params.vertices, params.edges);
  ParsePowerInput(params, inp);
}

void ParseHitsInput(HitsInput& params,
                    const std::string& fname) {
  std::ifstream inp{fname};
  ParseHitsParams(params, inp);
}
