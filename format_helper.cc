#include "format_helper.h"

#include <vector>

json MatrixToJson(const MatrixXd& m) {
  json r;
  r["rows"] = m.rows();
  r["cols"] = m.cols();

  // TODO: Improve this conversion
  std::vector<double> data;
  for (int i = 0; i < m.size(); ++i) {
    data.push_back(m.data()[i]);
  }
  r["data"] = data;
  return r;
}

std::ostream& operator<<(std::ostream& out, PageRankInput& params) {
  out << params.alpha << "\n"
      << params.vertices.size() << ": ";
  for (int v: params.vertices) {
    out << v << " ";
  }
  out << std::endl
      << params.edges.size() << ": ";
  for (auto& it: params.edges) {
    out << it.first << "-->" << it.second << "; ";
  }
  out << std::endl;
  out << params.GetEpsilon() << " "
      << params.GetMaxStep() << "\n";
  return out;
}