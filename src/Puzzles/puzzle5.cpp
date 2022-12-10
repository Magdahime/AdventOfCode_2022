#include "FileReader.hpp"
#include "Puzzles.hpp"
#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace AdventOfCode {

namespace Puzzles {

constexpr int GAP = 4;
constexpr int FIRST_CHAR_POS = 1;

struct Command {
  int howMany;
  int from;
  int to;
};

using Stack = std::deque<char>;

std::string getNextSSElem(std::stringstream &ss) {
  std::string temp;
  ss >> temp;
  return temp;
}

std::pair<std::vector<std::string>, std::vector<std::string>>
divideStackAndCommandLines(const std::vector<std::string> &lines) {

  auto divisionIt =
      std::find_if(lines.begin(), lines.end(),
                   [&](std::string line) { return line.empty(); });

  return std::make_pair(std::vector<std::string>(lines.begin(), divisionIt),
                        std::vector<std::string>(divisionIt + 1, lines.end()));
}

int getMaxStackIndex(const std::string &indexLine) {
  std::string temp;
  std::stringstream ss(indexLine);
  while (ss >> temp) {
  }
  return stoi(temp);
}

std::vector<Command>
parseCommands(const std::vector<std::string> &commandInfo) {

  std::vector<Command> commands;

  for (auto it = commandInfo.begin(); it != commandInfo.end(); it++) {

    std::stringstream ss(*it);
    getNextSSElem(ss);
    int howMany = stoi(getNextSSElem(ss));
    getNextSSElem(ss);
    int from = stoi(getNextSSElem(ss)) - 1;
    getNextSSElem(ss);
    int to = stoi(getNextSSElem(ss)) - 1;
    commands.push_back(Command{.howMany = howMany, .from = from, .to = to});
  }
  return commands;
}

std::vector<Stack> parseStacks(std::vector<std::string> stacksInfo) {

  int maxIndex = getMaxStackIndex(stacksInfo.back()) - 1;
  std::vector<Stack> stacks(maxIndex + 1);

  for (auto it = stacksInfo.begin(); it != stacksInfo.end() - 1; it++) {
    for (int i = 0; i < maxIndex; i++) {
      char c = (*it)[FIRST_CHAR_POS + i * GAP];
      if (c != ' ') {
        stacks[i].push_back(c);
      }
    }
  }

  return stacks;
}

void applyCommand(const Command &command, std::vector<Stack> &stacks) {

  for (auto i = 0; i < command.howMany; i++) {
    auto elemToMove = stacks[command.from].front();
    stacks[command.from].pop_front();
    stacks[command.to].push_front(elemToMove);
  }
}

void applyCommandV2(const Command &command, std::vector<Stack> &stacks) {
  std::vector<char> elementsToMove;
  for (auto i = 0; i < command.howMany; i++) {
    elementsToMove.push_back(stacks[command.from].front());
    stacks[command.from].pop_front();
  }

  for (auto i = 0; i < command.howMany; i++) {
    auto elemToMove = elementsToMove.back();
    stacks[command.to].push_front(elemToMove);
    elementsToMove.pop_back();
  }
}

void puzzle5(std::vector<std::string> arguments) {

  FileReader::FileReader fr(arguments[0]);
  std::vector<std::string> lines;

  while (!fr.eof()) {
    std::string line = fr.nextLine();
    lines.push_back(line);
  }

  auto pair = divideStackAndCommandLines(lines);

  auto stacks = parseStacks(pair.first);
  auto stacks2 = stacks;
  auto commands = parseCommands(pair.second);

  for (const auto &command : commands) {
    applyCommand(command, stacks);
  }

  for (const auto &command : commands) {
    applyCommandV2(command, stacks2);
  }

  for (const auto &stack : stacks) {
    std::cout << stack.front();
  }

  std::cout << "\n";
  
  for (const auto &stack : stacks2) {
    std::cout << stack.front();
  }
}

} // namespace Puzzles
} // namespace AdventOfCode