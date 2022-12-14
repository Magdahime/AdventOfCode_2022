#include "FileReader.hpp"
#include "Puzzles.hpp"
#include <algorithm>
#include <deque>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace AdventOfCode {

namespace Puzzles {

void noop(std::vector<int> &valueByTime) {
  valueByTime.push_back(valueByTime.back());
}
void addx(std::vector<int> &valueByTime, int valueToAdd) {
  valueByTime.push_back(valueByTime.back());
  valueByTime.push_back(valueByTime.back() + valueToAdd);
}

int getStrengthByCycle(int idx, const std::vector<int> &valueByTime) {
  std::cout << idx << " : " << valueByTime[idx] << "\n";
  return idx * valueByTime[idx];
}

void puzzle10(std::vector<std::string> arguments) {
  FileReader::FileReader fr(arguments[0]);
  std::vector<int> valueByTime{{1, 1}};

  while (!fr.eof()) {
    std::string line = fr.nextLine();
    if (line == "noop") {
      noop(valueByTime);
    } else {
      std::stringstream ss(line);
      std::string temp;
      int valuetoAdd;
      ss >> temp;
      ss >> valuetoAdd;
      addx(valueByTime, valuetoAdd);
    }
  }
  int sum = getStrengthByCycle(20, valueByTime) +
            getStrengthByCycle(60, valueByTime) +
            getStrengthByCycle(100, valueByTime) +
            getStrengthByCycle(140, valueByTime) +
            getStrengthByCycle(180, valueByTime) +
            getStrengthByCycle(220, valueByTime);
  std::cout << sum << "\n";

  for (auto i = 0; i < 6; i++) {
    for (auto j = 1; j < 41; j++) {
      auto currentPixel = i * 40 + j;
      auto currentSpritePosition = valueByTime[currentPixel];

      if (std::abs(j - 1 - currentSpritePosition) <= 1) {
        std::cout << "#";
      } else {
        std::cout << ".";
      }
    }
    std::cout << "\n";
  }
}

} // namespace Puzzles
} // namespace AdventOfCode