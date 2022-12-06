#include "Program.hpp"
#include "Puzzles.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<std::string> arguments;
  for (int i = 1; i < argc; ++i) {
    arguments.push_back(argv[i]);
  }

  AdventOfCode::Program::Program program(arguments);

  program.registerFunction(AdventOfCode::Puzzles::puzzle1);
  program.registerFunction(AdventOfCode::Puzzles::puzzle2);
  program.registerFunction(AdventOfCode::Puzzles::puzzle3);
  program.registerFunction(AdventOfCode::Puzzles::puzzle4);
  program.registerFunction(AdventOfCode::Puzzles::puzzle6);
  program.run();

  return 0;
}
