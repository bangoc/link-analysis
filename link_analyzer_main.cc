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
  double alpha = 0;
  double epsilon = 0.0001;
  int maxstep = 100;
  std::vector<int> vertices;
  std::vector<std::pair<int, int>> edges;
  std::vector<std::pair<int, double>> out;
  inp >> alpha;
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
  inp >> epsilon >> maxstep;
  json debug;
  PageRank(alpha, vertices, edges, epsilon, maxstep, out, debug, true);
  LOG(INFO) << "\nDebug\n" << debug.dump(2);
}

void CalculateHits(const std::string& fname) {
  std::ifstream inp{fname};
  double epsilon = 0.0001;
  int maxstep = 100;
  std::vector<int> vertices;
  std::vector<std::pair<int, int>> edges;
  std::vector<std::pair<int, double>> hubs;
  std::vector<std::pair<int, double>> auth;
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
  inp >> epsilon >> maxstep;

  json debug;
  Hits(vertices, edges, epsilon, maxstep, hubs, auth, debug, true);
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