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