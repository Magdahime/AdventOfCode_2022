#include "FileReader.hpp"
#include "Puzzles.hpp"
#include <algorithm>

namespace AdventOfCode {

namespace Puzzles {

void puzzle1(std::vector<std::string> arguments) {

  FileReader::FileReader fr(arguments[0]);
  std::vector<int> elvesCalories;
  int tempCalories = 0;

  while (!fr.eof()) {
    std::string line = fr.nextLine();

    if (line.empty()) {
      elvesCalories.push_back(tempCalories);
      tempCalories = 0;
    } else {
      tempCalories += stoi(line);
    }
  }
  elvesCalories.push_back(tempCalories);

  std::sort(elvesCalories.begin(), elvesCalories.end());

  std::cout << elvesCalories[elvesCalories.size() - 1] << '\n';

  auto sumOfNthelements = [=](int n, std::vector<int> numVector) -> int {
    int partialSum = 0;
    for (int i = 0; i < n; i++) {
      partialSum += numVector[numVector.size() - (i + 1)];
    }

    return partialSum;
  };

  std::cout << sumOfNthelements(3, elvesCalories) << '\n';
}

} // namespace Puzzles

} // namespace AdventOfCode