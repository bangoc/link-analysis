#include "base.h"
#include "input_helper.h"
#include "hits.h"
#include "pagerank.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include <glog/logging.h>

void CalculatePagerank(const std::string& fname) {
  PageRankInput params;
  ParsePageRankInput(params, fname);
  json debug;
  std::vector<std::pair<int, double>> out;
  PageRank(params, out, debug, true);
  LOG(INFO) << "\nDebug\n" << debug.dump(2);
}

void CalculateHits(const std::string& fname) {
  HitsInput params;
  std::vector<std::pair<int, double>> hubs;
  std::vector<std::pair<int, double>> auth;
  ParseHitsInput(params, fname);
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