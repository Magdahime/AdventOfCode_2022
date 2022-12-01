#include "Program.hpp"
#include "Puzzles.hpp"
#include <string>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<std::string> arguments;
  for (int i = 1; i < argc; ++i) {
    arguments.push_back(argv[i]);
  }

  AdventOfCode::Program::Program program(arguments);

  program.registerFunction(AdventOfCode::Puzzles::puzzle1);
  program.run();

  return 0;
}
