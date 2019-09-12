#include "pocker.h"
#include <string>

namespace pocker {
Score Hand::GetMostValuableScore() const {
  if (HasFourOfAKind())
    return FourOfAKind;
  if (HasStraight())
    return Straight;
  if (HasThreeOfAKind())
    return ThreeOfAKind;
  if (HasPair())
    return OnePair;
  return HighCard;
}
bool Hand::HasPair() const {
  for (auto const &card : hand) {
    int count{};
    for (auto const &others : hand) {
      if (card.face_value == others.face_value) {
        ++count;
      }
    }
    if (count >= 2) {
      return true;
    }
  }
  return false;
}
bool Hand::HasThreeOfAKind() const {
  for (auto const &card : hand) {
    int count{};
    for (auto const &others : hand) {
      if (card.face_value == others.face_value) {
        ++count;
      }
    }
    if (count >= 3) {
      return true;
    }
  }
  return false;
}
bool Hand::HasFourOfAKind() const {
  for (auto const &card : hand) {
    int count{};
    for (auto const &others : hand) {
      if (card.face_value == others.face_value) {
        ++count;
      }
    }
    if (count >= 4) {
      return true;
    }
  }
  return false;
}
bool Hand::HasStraight() const {
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
    return true;
  }
  return false;
}
std::optional<Card> Hand::GetFirstTieBreaker(Score score) const {
  if (OnePair == score) {
    for (auto const &card : hand) {
      int count{};
      for (auto const &others : hand) {
        if (card.face_value == others.face_value) {
          ++count;
          if (count == 2) {
            return card;
          }
        }
      }
    }
    return {};
  }
  return hand.back();
}

bool operator<(const Hand &lhs, const Hand &rhs) {
  if (lhs.GetMostValuableScore() < rhs.GetMostValuableScore()) {
    return true;
  } else if (lhs.GetMostValuableScore() == rhs.GetMostValuableScore()) {
    return lhs.GetFirstTieBreaker(rhs.GetMostValuableScore())
               .value()
               .face_value < rhs.GetFirstTieBreaker(lhs.GetMostValuableScore())
                                 .value()
                                 .face_value;
  }
  return false;
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