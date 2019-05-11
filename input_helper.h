#ifndef INPUT_HELPER_H_
#define INPUT_HELPER_H_

#include "base.h"

void ParsePageRankParams(PageRankInput& params,
                        std::istream& inp);

void ParseHitsParams(HitsInput& params,
                     std::istream& inp);

void ParsePageRankInput(PageRankInput& params,
                        const std::string& fname);

void ParseHitsInput(HitsInput& params,
                    const std::string& fname);

#endif  // INPUT_HELPER_H_