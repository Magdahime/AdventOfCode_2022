#include "FileReader.hpp"
#include <exception>

namespace AdventOfCode {

namespace FileReader {

std::string FileReader::nextLine() {

  if (!sourceFile_.is_open()) {
    sourceFile_.open(filename_.c_str());

    if (!sourceFile_) {
      throw std::runtime_error("Cannot open specified file");
    }
  }
  std::string tempLine;
  std::getline(sourceFile_, tempLine);
  lineCounter_++;
  return tempLine;
}

} // namespace FileReader

} // namespace AdventOfCode