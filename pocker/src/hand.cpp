#include <algorithm>
#include <numeric>

#include "hand.h"

namespace pocker {

Hand::Hand(Card c0, Card c1, Card c2, Card c3, Card c4)
    : hand{c0, c1, c2, c3, c4} {
  std::sort(hand.begin(), hand.end(), [](Card const &lhs, Card const &rhs) {
    return lhs.face_value < rhs.face_value;
  });
}

Score Hand::GetMostValuableScore() const {
  std::vector<std::underlying_type<FaceValue>::type> face_values;
  std::transform(hand.cbegin(), hand.cend(), std::back_inserter(face_values),
                 [](auto const &card) { return card.face_value; });

  std::vector<std::underlying_type<FaceValue>::type> diff;
  std::adjacent_difference(face_values.cbegin(), face_values.cend(),
                           std::back_inserter(diff));

  auto zeros = std::count(std::next(diff.cbegin()), diff.cend(),
                          std::underlying_type<FaceValue>::type{0});

  auto ones = std::count(std::next(diff.cbegin()), diff.cend(),
                         std::underlying_type<FaceValue>::type{1});

  if (zeros == 3)
    return Score{Score::FourOfAKind};
  if (ones == 4)
    return Score{Score::Straight};
  if (zeros == 2)
    return Score{Score::ThreeOfAKind};
  if (zeros == 1) {
    return Score{Score::OnePair, GetACardFromPair()};
  }
  return Score{Score::HighCard, hand.back()};
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