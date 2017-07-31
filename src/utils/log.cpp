#include "log.h"
#include <iostream>

namespace GameLib {

void Log(const std::string &text) {
  std::cout << std::endl;
  std::cout << "============================" << std::endl;
  std::cout << text << std::endl;
  std::cout << "============================" << std::endl;
  std::cout << std::endl;
}

} // namespace GameLib
