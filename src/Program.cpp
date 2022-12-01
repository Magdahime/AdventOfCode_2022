#include "Program.hpp"
#include <iostream>

namespace AdventOfCode {

namespace Program {

void Program::run() {

  if (arguments_.size() > 0) {

    puzzleFunctions_[stoi(arguments_[0])](
        std::vector<std::string>(arguments_.begin() + 1, arguments_.end()));
  }
}

void Program::registerFunction(
    std::function<void(std::vector<std::string>)> function) {

  puzzleFunctions_.push_back(function);
}

} // namespace Program
} // namespace AdventOfCode