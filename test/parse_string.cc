#include "base.h"
#include "format_helper.h"
#include "input_helper.h"

#include <sstream>
#include <iostream>

int main() {
  std::stringstream ss{"0.75 3 1 2 3 3 1 2 1 3 3 2 0.001 5"};
  PageRankInput params;
  ParsePageRankParams(params, ss);
  std::cout << params;
}