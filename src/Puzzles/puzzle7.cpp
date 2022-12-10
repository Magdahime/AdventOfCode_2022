#include "FileReader.hpp"
#include "Puzzles.hpp"
#include <algorithm>
#include <cstddef>
#include <deque>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

namespace AdventOfCode {

namespace Puzzles {

class Directory;

class File {

public:
  File(std::weak_ptr<Directory> parent, int size, std::string name)
      : parent_(parent), size_(size), name_(name) {}
  File() = default;
  std::weak_ptr<Directory> parent() { return parent_; }
  int size() { return size_; }
  std::string name() { return name_; }
  virtual std::shared_ptr<Directory> cd(std::string newDirectory) {
    throw std::runtime_error("Yo mama");
  }

  virtual ~File() = default;

protected:
  std::weak_ptr<Directory> parent_;
  int size_;
  std::string name_;
};

class Directory : public File, public std::enable_shared_from_this<Directory> {

public:
  Directory(std::weak_ptr<Directory> parent, int size, std::string name)
      : File(parent, size, name) {}
  Directory() = default;

  void addChild(std::shared_ptr<File> newChild) {
    children_.push_back(newChild);
    size_ += newChild->size();
  }

  void addChild(int size, std::string name) {
    children_.push_back(std::make_shared<File>(shared_from_this(), size, name));
    size_ += size;
  }

  const std::deque<std::shared_ptr<File>> &children() { return children_; }

  std::shared_ptr<Directory> cd(std::string newDirectory) override {
    if (newDirectory == "/") {
      auto result = shared_from_this();
      while (!result->parent_.expired()) {
        result = result->parent().lock();
      }
      return result;
    }
    if (newDirectory == "..") {
      if (parent_.lock())
        return parent_.lock();
      else
        shared_from_this();
    }

    auto it = std::find_if(children().begin(), children().end(),
                           [&](const std::shared_ptr<File> &file) {
                             return file->name() == newDirectory;
                           });
    if (it != children().end()) {
      return std::shared_ptr<Directory>(dynamic_cast<Directory *>(it->get()));
    }
    return std::shared_ptr<Directory>();
  }

  virtual ~Directory() = default;

private:
  void updateSize(int size) {
    if (!parent_.expired()) {
      File::parent_.lock()->updateSize(size);
    }
    size += size;
  }
  std::deque<std::shared_ptr<File>> children_;
};

void puzzle7(std::vector<std::string> arguments) {

  FileReader::FileReader fr(arguments[0]);
  std::shared_ptr<Directory> root =
      std::make_shared<Directory>(std::weak_ptr<Directory>(), 0, "/");
  std::shared_ptr<Directory> current = root;

  while (!fr.eof()) {
    std::string line = fr.nextLine();

    if (line.starts_with("$")) {
      std::cout << "command"
                << "\n";
      std::stringstream ss(std::string(line.begin() + 1, line.end()));

      std::string command = getNextSSElem(ss);
      if (command == "cd") {
        std::string directoryName = getNextSSElem(ss);
        current = current->cd(directoryName);
      }

    } else {
      if (line.starts_with("dir")) {
        std::cout << "dir"
                  << "\n";
        std::stringstream ss(std::string(line.begin() + 3, line.end()));
        std::string directoryName = getNextSSElem(ss);
        current->addChild(
            std::make_shared<Directory>(current, 0, directoryName));
      } else {
        std::cout << "file"
                  << "\n";
        std::stringstream ss(line);
        int size = stoi(getNextSSElem(ss));
        std::string name = getNextSSElem(ss);
        current->addChild(std::make_shared<File>(current, size, name));
      }
    }
  }

  std::cout << root->size() << "\n";
}

} // namespace Puzzles
} // namespace AdventOfCode