#include "FileReader.hpp"
#include "Puzzles.hpp"

namespace AdventOfCode {

namespace Puzzles {

using Range = std::pair<int, int>;

Range getRange(const std::string &elfString) {

  const auto hyphenIt = std::find(elfString.begin(), elfString.end(), '-');
  const auto beginRange = std::string(elfString.begin(), hyphenIt);
  const auto endRange = std::string(hyphenIt + 1, elfString.end());

  return std::make_pair(std::stoi(beginRange), std::stoi(endRange));
}

std::pair<Range, Range> getRanges(const std::string &line) {

  const auto commaIt = std::find(line.begin(), line.end(), ',');
  const auto firstElf = std::string(line.begin(), commaIt);
  const auto secondElf = std::string(commaIt + 1, line.end());

  return std::make_pair(getRange(firstElf), getRange(secondElf));
}

bool checkFullOverlap(Range range1, Range range2) {
  return ((range1.first <= range2.first) && (range1.second >= range2.second)) ||
         ((range1.first >= range2.first) && (range1.second <= range2.second));
}

bool checkAnyOverlap(Range range1, Range range2) {
  return ((range1.second >= range2.first) && (range2.second >= range1.first));
}

void puzzle4(std::vector<std::string> arguments) {

  FileReader::FileReader fr(arguments[0]);
  std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>
      elvesCleaningPairRanges;
  auto fullOverlappedCounter = 0;
  auto anyOverlappedCounter = 0;
  while (!fr.eof()) {
    std::string line = fr.nextLine();
    auto ranges = getRanges(line);
    if (checkFullOverlap(ranges.first, ranges.second))
      fullOverlappedCounter++;
    if (checkAnyOverlap(ranges.first, ranges.second))
      anyOverlappedCounter++;
  }

  std::cout << fullOverlappedCounter << "\n";
  std::cout << anyOverlappedCounter << "\n";
}

} // namespace Puzzles
} // namespace AdventOfCode