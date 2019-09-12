#include "pocker.h"
#include <string>

namespace pocker {
Score Hand::GetMostValuableScore() const {
  auto highest_score = HighCard;
  for (auto const &card : hand) {
    int count{};
    for (auto const &others : hand) {
      if (card.face_value == others.face_value) {
        ++count;
      }
    }
    if (count == 2) {
      highest_score = OnePair;
    }
    if (count == 3) {
      highest_score = ThreeOfAKind;
    }
    if (count == 4) {
      highest_score = FourOfAKind;
    }
  }
  auto begin = hand.cbegin();
  auto next = hand.cbegin();
  std::advance(next, 1);
  auto end = hand.cend();
  std::int32_t consecutive_face_value_count{};
  for (; next != end && begin != end; ++begin, ++next) {
    if ((*next).face_value == ((*begin).face_value + 1)) {
      ++consecutive_face_value_count;
    }
  }
  if (consecutive_face_value_count == 4) {
    highest_score = Straight;
  }
  return highest_score;
}
bool operator<(const Hand &lhs, const Hand &rhs) {
  return lhs.GetMostValuableScore() < rhs.GetMostValuableScore();
}
std::ostream &operator<<(std::ostream &os, const Card &p) {
  os << p.suit << " " << p.face_value;
  return os;
}
std::ostream &operator<<(std::ostream &os, const Hand &obj) {
  for (auto const &o : obj.hand) {
    os << o << "; ";
  }
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