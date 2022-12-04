#include "FileReader.hpp"
#include "Puzzles.hpp"

#include <array>

namespace AdventOfCode {

namespace Puzzles {

constexpr int LETTER_NUM = 55;

using RucksackCompartments = std::pair<std::string, std::string>;

int lowerCaseToNum(char c) { return (c - 'a') + 1; }
int upperCaseToNum(char c) { return (c - 'A') + 27; }

int letterToNum(char c) {
  return std::isupper(c) ? upperCaseToNum(c) : lowerCaseToNum(c);
}

std::pair<std::string, std::string>
splitStringInHalf(const std::string &string) {

  return std::make_pair(string.substr(0, string.length() / 2),
                        string.substr(string.length() / 2));
}

std::array<bool, LETTER_NUM>
findCommonCharsInTwoStrings(const std::string &string1,
                            const std::string &string2) {

  std::array<bool, LETTER_NUM> letterHashMap = {0};
  std::array<bool, LETTER_NUM> returnArray = {0};
  for (auto i = string1.begin(); i != string1.end(); i++) {
    letterHashMap[letterToNum(*i)] = true;
  }

  for (auto j = string2.begin(); j != string2.end(); j++) {
    auto charToNum = letterToNum(*j);
    if (letterHashMap[charToNum] == true) {
      returnArray[charToNum] = true;
    }
  }
  return returnArray;
}

int findBadge(const std::vector<std::string> &elfGroup) {

  auto firstHashMap = findCommonCharsInTwoStrings(elfGroup[0], elfGroup[1]);
  auto secondHashMap = findCommonCharsInTwoStrings(elfGroup[1], elfGroup[2]);

  for (auto i = 0; i < firstHashMap.size(); i++) {
    if (firstHashMap[i] && secondHashMap[i]) {
      return i;
    }
  }

  return 0;
}

void puzzle3(std::vector<std::string> arguments) {

  FileReader::FileReader fr(arguments[0]);
  auto sumOfPriorities = 0;
  auto sumOfGroupPriorities = 0;

  std::vector<std::string> groupingVector;
  auto groupCounter = 0;

  while (!fr.eof()) {
    std::string line = fr.nextLine();
    auto splittedString = splitStringInHalf(line);
    auto resultHashMap = findCommonCharsInTwoStrings(splittedString.first,
                                                     splittedString.second);

    sumOfPriorities += std::distance(
        resultHashMap.begin(),
        std::find(resultHashMap.begin(), resultHashMap.end(), true));

    groupingVector.push_back(line);
    groupCounter++;
    if (groupCounter == 3) {

      sumOfGroupPriorities += findBadge(groupingVector);

      groupingVector.clear();
      groupCounter = 0;
    }
  }

  std::cout << "Priorities sum: " << sumOfPriorities << "\n";
  std::cout << "Group priorities sum: " << sumOfGroupPriorities << "\n";
}
} // namespace Puzzles
} // namespace AdventOfCode