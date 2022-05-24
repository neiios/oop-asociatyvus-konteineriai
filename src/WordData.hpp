#pragma once

#include <vector>

class WordData {
 public:
  int count = 1;
  // save line numbers to vector
  std::vector<int> lineIndices;

  WordData(int lineIndex) { lineIndices.push_back(lineIndex); }
};
