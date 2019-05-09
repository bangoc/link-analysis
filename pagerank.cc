#include "pagerank.h"

#include <fstream>
#include <iostream>
#include <string>
#include <glog/logging.h>

void PageRank(double alpha,
              std::vector<int>& vertices,
              std::vector<std::pair<int, int>>& edges,
              double epsilon,
              const int maxstep,
              std::vector<std::pair<int, double>>& out) {
  std::map<int, int> id;
  std::map<int, int> iid;
  int i = 0;
  for (int v: vertices) {
    if (id.find(v) == id.end()) {
      DLOG(INFO) << v << " " << i;
      id[v] = i;
      iid[i] = v;
      ++i;
    }
  }
  const int n = id.size();
  MatrixXd t = MatrixXd::Zero(n, n);
  std::map<int, int> ones;
  for (int i = 0; i < n; ++i) {
    ones[i] = 0;
  }
  for (auto& it: edges) {
    int b = id[it.first];
    int e = id[it.second];
    DLOG(INFO) << b << " " << e << " "
              << it.first << " " << it.second;
    t(b, e) = 1;
    ones[b] += 1;
  }
  LOG(INFO) << "Ma tran ke:\n" << t << std::endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      t(i, j) = ones[i] > 0 ? t(i, j) / ones[i]: 1.0 / n;
    }
  }
  LOG(INFO) << "Ket qua buoc 1 va 2:\n" << t << std::endl;
  t *= (1 - alpha);
  LOG(INFO) << "Ket qua sau khi thuc hien buoc 3: \n"
            << t << std::endl;
  t += MatrixXd::Constant(n, n, alpha/n);
  LOG(INFO) << "Ma tran chuyen trang thai la: \n"
            << t << std::endl;
  MatrixXd p1 = MatrixXd::Constant(1, n, 1.0 / n);
  MatrixXd p2 = MatrixXd::Constant(1, n, 1.0 / n);
  double distance = 1.0;
  int step = 0;
  while (distance > epsilon || step >= maxstep) {
    p2 = p1 * t;
    LOG(INFO) << "step " << step << ": " << p1
              << " | " << p2 << std::endl;
    distance = 0;
    for (int i = 0; i < n; ++i) {
      distance += (p2(0, i) - p1(0, i)) * (p2(0, i) - p1(0, i));
    }
    DLOG(INFO) << "distance: " << distance;
    p1 = p2;
    ++step;
  }
  out.clear();
  for (auto& it: iid) {
    double pr = p1(0, it.first);
    LOG(INFO) << "Pagerank: \n" << it.second
              << " " << pr << std::endl;
    out.push_back(std::make_pair(it.second, pr));
  }
}
