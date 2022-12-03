#include "FileReader.hpp"
#include "Puzzles.hpp"
#include <algorithm>
#include <map>

namespace AdventOfCode {

namespace Puzzles {

constexpr int WIN = 6;
constexpr int DRAW = 3;
constexpr int LOSE = 0;

constexpr int ROCK = 1;
constexpr int PAPER = 2;
constexpr int SCISSORS = 3;

int rockPaperScissors(int me, int opponent) {

  int normalization = 1 - me;
  int meNormalized = me + normalization;
  int opponentNormalized = opponent + normalization + 3;
  opponentNormalized %= 3;

  if (meNormalized > opponentNormalized) {
    return me + WIN;
  } else if (opponentNormalized > meNormalized) {
    return me + LOSE;
  } else {
    return me + DRAW;
  }

  return 0;
}

int rockPaperScissorsWithKnownScore(int opponent, int expectedEnding) {

  int normalization = 1 - opponent;
  int opponentNormalized = opponent + normalization;
  int meNormalized = 0;

  if (expectedEnding == WIN) {
    meNormalized = opponentNormalized + 1;
  } else if (expectedEnding == DRAW) {
    meNormalized = opponentNormalized;
  } else {
    meNormalized = opponentNormalized - 1;
  }

  int me = meNormalized - normalization;

  if (me == 0) {
    me = 3;
  }
  if (me == 4) {
    me = 1;
  }

  std::cout << expectedEnding << " " << me << " " << opponent << "\n";

  return me + expectedEnding;
}

void puzzle2(std::vector<std::string> arguments) {

  std::map<char, int> charMapping{{'A', ROCK}, {'B', PAPER}, {'C', SCISSORS},
                                  {'X', ROCK}, {'Y', PAPER}, {'Z', SCISSORS}};

  std::map<char, int> charMappingWithEnding{{'A', ROCK},     {'B', PAPER},
                                            {'C', SCISSORS}, {'X', LOSE},
                                            {'Y', DRAW},     {'Z', WIN}};

  FileReader::FileReader fr(arguments[0]);
  std::vector<std::pair<int, int>> strategiesVector;
  int scoreSum = 0;
  int scoreSumExpectedEnd = 0;

  while (!fr.eof()) {
    std::string line = fr.nextLine();
    int opponent = charMapping[line[0]];
    int me = charMapping[line[2]];
    int expectedEnding = charMappingWithEnding[line[2]];

    scoreSum += rockPaperScissors(me, opponent);
    scoreSumExpectedEnd +=
        rockPaperScissorsWithKnownScore(opponent, expectedEnding);
  }

  std::cout << scoreSum << '\n';
  std::cout << scoreSumExpectedEnd << '\n';
}

} // namespace Puzzles
} // namespace AdventOfCode