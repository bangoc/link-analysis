#include "hits.h"

#include "format_helper.h"
#include "pagerank.h"

#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <glog/logging.h>

namespace {

void Normalize(MatrixXd& m) {
  if (m.size() > 0) {
    auto* d = m.data();
    double max = d[0];
    for (int i = 0; i < m.size(); ++i) {
      if (max < d[i]) {
        max = d[i];
      }
    }
    if (max > 0) {
      for (int i = 0; i < m.size(); ++i) {
        d[i] /= max;
      }
    }
  }
}

void InternalHits(HitsInput& inp,
          std::vector<std::pair<int, double>>& hubs,
          std::vector<std::pair<int, double>>& auth,
          json& debug,
          bool is_debug) {
  std::map<int, int> id;
  std::map<int, int> iid;
  int i = 0;
  for (int v: inp.vertices) {
    if (id.find(v) == id.end()) {
      DLOG(INFO) << v << " " << i;
      id[v] = i;
      iid[i] = v;
      ++i;
    }
  }
  if (is_debug) {
    debug["internal_id"] = id;
  }
  const int n = id.size();
  MatrixXd am = MatrixXd::Zero(n, n);
  for (auto& it: inp.edges) {
    int b = id[it.first];
    int e = id[it.second];
    DLOG(INFO) << b << " " << e << " "
              << it.first << " " << it.second;
    am(b, e) = 1;
  }
  MatrixXd amt = am.transpose();
  LOG(INFO) << "Ma tran ke:\n" << am << std::endl;
  LOG(INFO) << "Ma tran chuyen vi:\n" << amt << std::endl;
  if (is_debug) {
    debug["A"] = MatrixToJson(am);
    debug["At"] = MatrixToJson(amt);
  }
  MatrixXd aat = am * amt;
  MatrixXd ata = amt * am;
  LOG(INFO) << "\nAAt\n" << aat << std::endl
            << "AtA\n" << ata << std::endl;
  if (is_debug) {
    debug["AAt"] = MatrixToJson(aat);
    debug["AtA"] = MatrixToJson(ata);
  }
  MatrixXd h1 = MatrixXd::Constant(n, 1, 1);
  MatrixXd h2 = MatrixXd::Constant(n, 1, 1);
  double distance = 1.0;
  int step = 0;
  LOG(INFO) << "hubs: " << std::endl;
  if (is_debug) {
    debug["steps"] = json::array();
  }
  while (distance > inp.GetEpsilon() &&
         step < inp.GetMaxStep()) {
    h2 = aat * h1;
    Normalize(h2);
    LOG(INFO) << "step " << step << ": " << h1.transpose()
              << " | " << h2.transpose() << std::endl;
    distance = 0;
    for (int i = 0; i < n; ++i) {
      distance += std::pow(h2(i, 0) - h1(i, 0), 2);
    }
    DLOG(INFO) << "distance: " << distance;
    if (is_debug) {
      json tmp;
      tmp["step"] = step;
      tmp["distance"] = distance;
      tmp["hubs"] = MatrixToJson(h1);
      debug["steps"].push_back(tmp);
    }
    h1 = h2;
    ++step;
  }
  MatrixXd a1 = amt * h1;
  Normalize(a1);
  hubs.clear();
  for (auto& it: iid) {
    double hub_score = h1(it.first, 0);
    double auth_score = a1(it.first, 0);
    LOG(INFO) << "Hub & Authority scores: \n" << it.second
              << ": " << hub_score << " " << auth_score << std::endl;
    hubs.push_back(std::make_pair(it.second, hub_score));
    auth.push_back(std::make_pair(it.second, auth_score));
  }
  if (is_debug) {
    debug["external_id"] = iid;
    debug["hubs"] = MatrixToJson(h1);
    debug["auth"] = MatrixToJson(a1);
  }
}

}  // namespace

void Hits(HitsInput& inp,
          std::vector<std::pair<int, double>>& hubs,
          std::vector<std::pair<int, double>>& auth,
          json& debug,
          bool is_debug) {
  try {
    InternalHits(inp, hubs, auth, debug, is_debug);
  } catch (...) {
    debug["exception"] = true;
  }
}