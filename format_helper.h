#ifndef FORMAT_HELPER_H_
#define FORMAT_HELPER_H_

#include "base.h"

#include <iostream>

json MatrixToJson(const MatrixXd& m);
std::ostream& operator<<(std::ostream& out, PageRankInput& params);

#endif  // FORMAT_HELPER_H_