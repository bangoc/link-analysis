#include "base.h"
#include "hits.h"
#include "pagerank.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include <glog/logging.h>

void CalculatePagerank(const std::string& fname) {
  std::ifstream inp{fname};
  PageRankInput params;
  std::vector<std::pair<int, double>> out;
  inp >> params.alpha;
  int n = 0;
  inp >> n;
  for (int i = 0; i < n; ++i) {
    int v;
    inp >> v;
    params.vertices.push_back(v);
  }
  int m = 0;
  inp >> m;
  for (int i = 0; i < m; ++i) {
    int b, e;
    inp >> b >> e;
    params.edges.push_back(std::make_pair(b, e));
  }
  inp >> params.epsilon >> params.maxstep;
  json debug;
  PageRank(params, out, debug, true);
  LOG(INFO) << "\nDebug\n" << debug.dump(2);
}

void CalculateHits(const std::string& fname) {
  std::ifstream inp{fname};
  HitsInput params;
  std::vector<std::pair<int, double>> hubs;
  std::vector<std::pair<int, double>> auth;
  int n = 0;
  inp >> n;
  for (int i = 0; i < n; ++i) {
    int v;
    inp >> v;
    params.vertices.push_back(v);
  }
  int m = 0;
  inp >> m;
  for (int i = 0; i < m; ++i) {
    int b, e;
    inp >> b >> e;
    params.edges.push_back(std::make_pair(b, e));
  }
  inp >> params.epsilon >> params.maxstep;

  json debug;
  Hits(params, hubs, auth, debug, true);
  LOG(INFO) << "\nDebug:\n" << debug.dump(2);
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  if (argc != 3) {
    std::cout << "Usage: \n"
              << "  ./la pagerank input_file\n"
              << "  ./la hits input_file\n";
    return 1;
  }
  if (std::string(argv[1]) == "pagerank") {
    CalculatePagerank(argv[2]);
  } else if (std::string(argv[1]) == "hits") {
    CalculateHits(argv[2]);
  } else {
    LOG(ERROR) << "Unknown command";
  }
}