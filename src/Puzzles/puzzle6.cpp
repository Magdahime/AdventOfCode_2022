#include "FileReader.hpp"
#include "Puzzles.hpp"
#include <algorithm>
#include <deque>
#include <set>

namespace AdventOfCode {

namespace Puzzles {


void findNUnique(const std::string& datastream, int n){

  std::deque<char> frame(datastream.begin(), datastream.begin() + n);
  std::set<char> uniqueSet(datastream.begin(), datastream.begin() + n);

  for (auto it = datastream.begin() + n; it != datastream.end(); it++) {

    if (uniqueSet.size() == n) {
      std::cout << std::distance(datastream.begin(), it) << "\n";
      return;
    } else {
      auto popped = frame.front();
      frame.pop_front();
      if (std::find(frame.begin(), frame.end(), popped) == frame.end()) {
        uniqueSet.erase(popped);
      }
      frame.push_back(*it);
      uniqueSet.insert(*it);
    }
  }

}


void puzzle6(std::vector<std::string> arguments) {

  FileReader::FileReader fr(arguments[0]);

  std::string datastream = fr.nextLine();

  findNUnique(datastream, 4);
  findNUnique(datastream, 14);

}
} // namespace Puzzles
} // namespace AdventOfCode