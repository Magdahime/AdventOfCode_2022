#include "FileReader.hpp"
#include "Puzzles.hpp"
#include <algorithm>
#include <deque>
#include <iterator>
#include <set>
#include <vector>

namespace AdventOfCode {

namespace Puzzles {

struct MaxValueInEachDirection {
  int up = 0;
  int down = 0;
  int left = 0;
  int right = 0;
};

std::vector<int> createTreeLineFromString(std::string line) {
  std::vector<int> treeLine;
  for (auto c : line) {
    treeLine.push_back(c - '0');
  }
  return treeLine;
}

std::vector<int>
getNthColumn(const std::vector<std::vector<int>> &referenceVector, int column) {
  std::vector<int> columnVector;

  for (int i = 0; i < referenceVector.size(); i++) {
    columnVector.push_back(referenceVector[i][column]);
  }
  return columnVector;
}

std::vector<std::vector<MaxValueInEachDirection>>
createMaxHeightMap(const std::vector<std::vector<int>> &treeMap) {

  std::vector<std::vector<MaxValueInEachDirection>> heightMap;
  heightMap.resize(treeMap.size());
  for (auto &row : heightMap) {
    row.resize(treeMap[0].size());
  }

  for (int row = 0; row < treeMap.size(); row++) {
    for (int column = 0; column < treeMap[0].size(); column++) {

      auto columnVector = getNthColumn(treeMap, column);
      auto maxHeight = MaxValueInEachDirection{
          .up = row == 0 ? -1
                         : *std::max_element(columnVector.begin(),
                                             columnVector.begin() + row),
          .down = row == treeMap.size() - 1
                      ? -1
                      : *std::max_element(columnVector.begin() + row + 1,
                                          columnVector.end()),
          .left = column == 0
                      ? -1
                      : *std::max_element(treeMap[row].begin(),
                                          treeMap[row].begin() + column),
          .right = column == treeMap[0].size() - 1
                       ? -1
                       : *std::max_element(treeMap[row].begin() + column + 1,
                                           treeMap[row].end())};
      heightMap[row][column] = maxHeight;
    }
  }

  return heightMap;
}

std::vector<std::vector<int>>
createScenicScoreMap(const std::vector<std::vector<int>> &treeMap) {

  std::vector<std::vector<int>> scenicScoreMap;
  scenicScoreMap.resize(treeMap.size());
  for (auto &row : scenicScoreMap) {
    row.resize(treeMap[0].size());
  }

  for (int row = 0; row < treeMap.size(); row++) {
    for (int column = 0; column < treeMap[0].size(); column++) {

      auto columnVector = getNthColumn(treeMap, column);

      const auto currentHeight = treeMap[row][column];

      auto scenicScore = MaxValueInEachDirection{
          .up = static_cast<int>(
              row == 0 ? 0
                       : std::abs(std::distance(
                             columnVector.rend() - row - 1,
                             std::find_if(columnVector.rbegin() +
                                              (columnVector.size() - row),
                                          columnVector.rend() - 1,
                                          [&](int treeHeight) {
                                            return treeHeight >= currentHeight;
                                          })))),
          .down = static_cast<int>(
              row == treeMap.size() - 1
                  ? 0
                  : std::abs(std::distance(
                        columnVector.begin() + row,
                        std::find_if(columnVector.begin() + row + 1,
                                     columnVector.end() - 1,
                                     [&](int treeHeight) {
                                       return treeHeight >= currentHeight;
                                     })))),

          .left = static_cast<int>(
              column == 0 ? 0
                          : std::abs(std::distance(
                                treeMap[row].rend() - column - 1,
                                std::find_if(treeMap[row].rbegin() +
                                                 (treeMap[row].size() - column),
                                             treeMap[row].rend() - 1,
                                             [&](int treeHeight) {
                                               return treeHeight >=
                                                      currentHeight;
                                             })))),
          .right = static_cast<int>(
              column == treeMap[0].size() - 1
                  ? 0
                  : std::abs(std::distance(treeMap[row].begin() + column,
                                           std::find_if(treeMap[row].begin() +
                                                            column + 1,
                                                        treeMap[row].end() - 1,
                                                        [&](int treeHeight) {
                                                          return treeHeight >=
                                                                 currentHeight;
                                                        }))))};

      scenicScoreMap[row][column] = scenicScore.up * scenicScore.down *
                                    scenicScore.left * scenicScore.right;
    }
  }

  return scenicScoreMap;
}

void puzzle8(std::vector<std::string> arguments) {
  FileReader::FileReader fr(arguments[0]);

  std::vector<std::vector<int>> treeMap;

  while (!fr.eof()) {
    std::string line = fr.nextLine();
    treeMap.push_back(createTreeLineFromString(line));
  }

  auto heightMap = createMaxHeightMap(treeMap);
  auto scenicScoreMap = createScenicScoreMap(treeMap);

  int visibleTrees = 0;
  for (int row = 0; row < treeMap.size(); row++) {
    for (int column = 0; column < treeMap[0].size(); column++) {

      int treeHeight = treeMap[row][column];
      MaxValueInEachDirection maxHeights = heightMap[row][column];

      if (treeHeight > maxHeights.up || treeHeight > maxHeights.down ||
          treeHeight > maxHeights.left || treeHeight > maxHeights.right) {
        visibleTrees++;
      }
    }
  }

  std::cout << visibleTrees << "\n";

  auto max = 0;
  for (auto line : scenicScoreMap) {
    for (auto scenicScore : line) {
      if (scenicScore > max) {
        max = scenicScore;
      }
    }
  }

  std::cout << max << "\n";
}

} // namespace Puzzles
} // namespace AdventOfCode