
#pragma once

#include <iostream>

namespace hpgcc {

class HPGCC {
public:
  void read(std::string filename) { this->filename = filename; }
  bool shuffle() {
    this->shuffled = true;
    return this->shuffled;
  }
  double colorGreedy(double param1) { return param1 * 10; }
  std::string filename;
  bool shuffled;
};
}