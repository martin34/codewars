
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "hand.h"
#include "parser.h"

int main(int argc, char *argv[]) {
  std::ignore = argc;
  std::ignore = argv;

  std::filesystem::path input_file{
      "/home/martin/repo/codewars/pocker/pocker.txt"};
  std::ifstream in{input_file};
  std::string tmp;
  std::int32_t player_one_win_count{0};
  std::int32_t player_two_win_count{0};
  std::int32_t tie_count{0};
  while (std::getline(in, tmp)) {
    if (tmp.size() > 0) {
      auto hands = pocker::ParseHandsFromLine(tmp);
      if (hands.first != hands.second) {
        hands.first < hands.second ? ++player_two_win_count
                                   : ++player_one_win_count;
      } else {
        std::cout << "Tie with 1: " << hands.first << " 2: " << hands.second
                  << std::endl;
        ++tie_count;
      }
    }
  }
  std::cout << "Player one won: " << player_one_win_count << std::endl;
  std::cout << "Player two won: " << player_two_win_count << std::endl;
  std::cout << "Numer of games with tie: " << tie_count << std::endl;
}