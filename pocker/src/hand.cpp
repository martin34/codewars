#include <algorithm>
#include <numeric>

#include "hand.h"

namespace pocker {

using FaceValueTypeVector = std::vector<std::underlying_type<FaceValue>::type>;

Hand::Hand(Card c0, Card c1, Card c2, Card c3, Card c4)
    : hand{c0, c1, c2, c3, c4} {
  std::sort(hand.begin(), hand.end(), [](Card const &lhs, Card const &rhs) {
    return lhs.face_value < rhs.face_value;
  });
}

std::optional<Score> GetStraight(FaceValueTypeVector const &diff,
                                 std::vector<Card> const &hand) {
  auto ones = std::count(std::next(diff.cbegin()), diff.cend(),
                         std::underlying_type<FaceValue>::type{1});
  if (ones == 4) {
    return std::optional{Score{Score::Straight, hand.back()}};
  }
  return {};
}
std::optional<Score> GetFourOfAKind(std::int32_t zeros,
                                    FaceValueTypeVector const &diff,
                                    std::vector<Card> const &hand) {
  if (zeros != 3) {
    return {};
  }
  auto position_with_card = std::find(diff.cbegin(), diff.cend(), 0);
  auto distance = std::distance(diff.cbegin(), position_with_card);
  auto card = hand.cbegin();
  std::advance(card, distance);
  return std::optional{Score{Score::FourOfAKind, *card}};
}
std::optional<Score> GetThreeOfAKind(std::int32_t zeros,
                                     FaceValueTypeVector const &diff,
                                     std::vector<Card> const &hand) {
  if (zeros != 2) {
    return {};
  }
  auto position_with_card = std::find(diff.cbegin(), diff.cend(), 0);
  auto distance = std::distance(diff.cbegin(), position_with_card);
  auto card = hand.cbegin();
  std::advance(card, distance);
  return std::optional{Score{Score::ThreeOfAKind, *card}};
}
std::optional<Score> GetPair(std::int32_t zeros,
                             FaceValueTypeVector const &diff,
                             std::vector<Card> hand) {
  if (zeros != 1) {
    return {};
  }
  auto position_with_card = std::find(diff.cbegin(), diff.cend(), 0);
  auto distance = std::distance(diff.cbegin(), position_with_card);
  auto card = hand.cbegin();
  std::advance(card, distance);
  return std::optional{Score{Score::OnePair, *card}};
}
Score Hand::GetMostValuableScore() const {
  FaceValueTypeVector face_values;
  std::transform(hand.cbegin(), hand.cend(), std::back_inserter(face_values),
                 [](auto const &card) { return card.face_value; });

  FaceValueTypeVector diff;
  std::adjacent_difference(face_values.cbegin(), face_values.cend(),
                           std::back_inserter(diff));

  auto zeros = std::count(std::next(diff.cbegin()), diff.cend(),
                          std::underlying_type<FaceValue>::type{0});

  auto four_of_a_kind = GetFourOfAKind(zeros, diff, hand);
  if (four_of_a_kind) {
    return four_of_a_kind.value();
  }
  auto straight = GetStraight(diff, hand);
  if (straight) {
    return straight.value();
  }
  auto three_of_a_kind = GetThreeOfAKind(zeros, diff, hand);
  if (three_of_a_kind) {
    return three_of_a_kind.value();
  }
  auto pair = GetPair(zeros, diff, hand);
  if (pair) {
    return pair.value();
  }
  return Score{Score::HighCard, hand.back()};
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