
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::ignore = argc;
  std::ignore = argv;

  std::filesystem::path input_file{
      "/home/martin/repo/codewars/pocker/pocker.txt"};
  std::ifstream in{input_file};
  std::vector<std::string> lines_;
  std::string tmp;
  while (std::getline(in, tmp)) {
    if (tmp.size() > 0) {
      lines_.push_back(tmp);
    }
  }
  std::cout << "File found and opened: " << in.is_open() << std::endl;
  std::cout << lines_.at(1);
  // Parse lines to two hands

  // determine winner and count
}