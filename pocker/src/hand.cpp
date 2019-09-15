#include "hand.h"
#include <algorithm>

namespace pocker {

Hand::Hand(Card c0, Card c1, Card c2, Card c3, Card c4)
    : hand{c0, c1, c2, c3, c4} {
  std::sort(hand.begin(), hand.end(), [](Card const &lhs, Card const &rhs) {
    return lhs.face_value < rhs.face_value;
  });
}

Score Hand::GetMostValuableScore() const {
  if (HasFourOfAKind())
    return Score{Score::FourOfAKind};
  if (HasStraight())
    return Score{Score::Straight};
  if (HasThreeOfAKind())
    return Score{Score::ThreeOfAKind};
  if (HasPair())
    return Score{Score::OnePair, GetACardFromPair()};
  return Score{Score::HighCard, hand.back()};
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
Card Hand::GetACardFromPair() const {
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
  std::logic_error{"No Pair found"};
  return {Heart, Two};
}

bool operator<(const Hand &lhs, const Hand &rhs) {
  auto lhs_score = lhs.GetMostValuableScore();
  auto rhs_score = rhs.GetMostValuableScore();
  if (lhs_score < rhs_score) {
    return true;
  } else if (lhs_score == rhs_score) {
    return lhs_score.GetFirstTieBreaker().value().face_value <
           rhs_score.GetFirstTieBreaker().value().face_value;
  }
  return false;
}
std::ostream &operator<<(std::ostream &os, const Hand &obj) {
  for (auto const &o : obj.hand) {
    os << o << "; ";
  }
  return os;
}
} // namespace pocker