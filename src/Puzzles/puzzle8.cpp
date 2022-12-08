#include "FileReader.hpp"
#include "Puzzles.hpp"
#include <algorithm>
#include <deque>
#include <set>
#include <vector>

namespace AdventOfCode {

namespace Puzzles {

struct MaxHeightInEachDirection {
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

std::vector<std::vector<MaxHeightInEachDirection>>
createMaxHeightMap(const std::vector<std::vector<int>> &treeMap) {

  std::vector<std::vector<MaxHeightInEachDirection>> heightMap;
  heightMap.resize(treeMap.size());
  for (auto &row : heightMap) {
    row.resize(treeMap[0].size());
  }

  for (int row = 0; row < treeMap.size(); row++) {
    for (int column = 0; column < treeMap[0].size(); column++) {

      auto columnVector = getNthColumn(treeMap, column);
      auto maxHeight = MaxHeightInEachDirection{
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

void puzzle8(std::vector<std::string> arguments) {
  FileReader::FileReader fr(arguments[0]);

  std::vector<std::vector<int>> treeMap;

  while (!fr.eof()) {
    std::string line = fr.nextLine();
    treeMap.push_back(createTreeLineFromString(line));
  }

  auto heightMap = createMaxHeightMap(treeMap);

  int visibleTrees = 0;
  for (int row = 0; row < treeMap.size(); row++) {
    for (int column = 0; column < treeMap[0].size(); column++) {

      int treeHeight = treeMap[row][column];
      MaxHeightInEachDirection maxHeights = heightMap[row][column];

      std::cout << maxHeights.up << " " << maxHeights.down << " "
                << maxHeights.left << " " << maxHeights.right << "\n";
      if (treeHeight > maxHeights.up || treeHeight > maxHeights.down ||
          treeHeight > maxHeights.left || treeHeight > maxHeights.right) {
        std::cout << row << " " << column << ": Visible " << treeHeight << "\n";
        visibleTrees++;
      }
    }
  }

  std::cout << visibleTrees << "\n";
}

} // namespace Puzzles
} // namespace AdventOfCode