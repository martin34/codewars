#include <string>
#include <vector>

#include "pocker/card.h"

namespace pocker {

std::ostream &operator<<(std::ostream &os, const Card &p) {
  os << p.suit << " " << p.face_value;
  return os;
}
std::ostream &operator<<(std::ostream &os, const FaceValue &p) {
  const std::vector<std::string> suit_string{
      "Two",  "Three", "Four", "Five",  "Six",  "Seven", "Eight",
      "Nine", "Ten",   "Jack", "Queen", "King", "Ace"};
  os << suit_string.at(p);
  return os;
}
std::ostream &operator<<(std::ostream &os, const Suit &p) {
  const std::vector<std::string> suit_string{"Heart", "Tile", "Clover", "Pike"};
  os << suit_string.at(p);
  return os;
}
} // namespace pocker