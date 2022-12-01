#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

namespace AdventOfCode {

namespace FileReader {

class FileReader {

public:
  FileReader(std::string filename) : filename_(filename), lineCounter_(0) {}
  std::string nextLine();
  bool eof() { return sourceFile_.eof(); }

  uint64_t lineCounter() { return lineCounter_; }

private:
  std::string filename_;
  uint64_t lineCounter_;
  std::fstream sourceFile_;
};

} // namespace FileReader

} // namespace AdventOfCode