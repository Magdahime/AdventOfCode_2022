#include "FileReader.hpp"
#include "Puzzles.hpp"
#include <algorithm>
#include <array>
#include <cstdlib>
#include <deque>
#include <iterator>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

namespace AdventOfCode {

namespace Puzzles {

constexpr int KNOTS_NUM = 10;

enum class Direction { UP = 'U', DOWN = 'D', LEFT = 'L', RIGHT = 'R' };

struct NextMove {

  Direction direction;
  int steps;
};

using Position = std::pair<int, int>;

Position moveHead(const Position &currHeadPosition, Direction newDirection) {

  Position newHeadPosition = currHeadPosition;
  switch (newDirection) {

  case Direction::UP:
    newHeadPosition.second++;
    break;
  case Direction::DOWN:
    newHeadPosition.second--;
    break;
  case Direction::LEFT:
    newHeadPosition.first--;
    break;
  case Direction::RIGHT:
    newHeadPosition.first++;
    break;

  default:
    break;
  }
  return newHeadPosition;
}

Position moveTail(const Position &currTailPosition, Position headPosition) {

  Position nextTailPosition = currTailPosition;
  auto XDiff = currTailPosition.first - headPosition.first;
  auto YDiff = currTailPosition.second - headPosition.second;

  // Move Tail in X Axis
  if (XDiff > 0) {
    nextTailPosition.first--;
  } else if (XDiff < 0) {
    nextTailPosition.first++;
  }
  // Move Tail in Y Axis
  if (YDiff > 0) {
    nextTailPosition.second--;
  } else if (YDiff < 0) {
    nextTailPosition.second++;
  }
  return nextTailPosition;
}

Direction getDirection(std::string s) {
  if (s == "U")
    return Direction::UP;
  else if (s == "D")
    return Direction::DOWN;
  else if (s == "L")
    return Direction::LEFT;
  return Direction::RIGHT;
}

void puzzle9(std::vector<std::string> arguments) {
  FileReader::FileReader fr(arguments[0]);

  std::set<Position> tailPositions;
  Position headPosition = {0, 0};
  Position tailPosition = {0, 0};
  tailPositions.insert(tailPosition);


  while (!fr.eof()) {
    std::string line = fr.nextLine();
    std::stringstream ss(line);

    NextMove move{.direction = getDirection(getNextSSElem(ss)),
                  .steps = std::stoi(getNextSSElem(ss))};

    for (auto i = 0; i < move.steps; i++) {
      auto newHeadPosition = moveHead(headPosition, move.direction);
      auto newTailPosition = tailPosition;
      if (std::abs(newHeadPosition.first - tailPosition.first) > 1 ||
          std::abs(newHeadPosition.second - tailPosition.second) > 1) {
        newTailPosition = moveTail(tailPosition, newHeadPosition);
      }

      tailPositions.insert(newTailPosition);
      headPosition = newHeadPosition;
      tailPosition = newTailPosition;
    }
  }

  std::cout << tailPositions.size() << "\n";
}
} // namespace Puzzles
} // namespace AdventOfCode