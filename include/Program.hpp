#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace AdventOfCode {

namespace Program {

class Program {

public:
  Program(std::vector<std::string> arguments)
      : arguments_(std::move(arguments)) {}

  void registerFunction(std::function<void(std::vector<std::string>)> function);
  void run();

private:
  std::vector<std::function<void(std::vector<std::string>)>> puzzleFunctions_;
  std::vector<std::string> arguments_;
};

} // namespace Program
} // namespace AdventOfCode