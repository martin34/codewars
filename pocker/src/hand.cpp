#include <algorithm>
#include <iostream>
#include <numeric>

#include "hand.h"

namespace pocker {

using FaceValueType = std::underlying_type<FaceValue>::type;
using FaceValueTypeVector = std::vector<FaceValueType>;
constexpr FaceValueType DontCareValue =
    std::numeric_limits<FaceValueType>::max();

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
    return std::optional{Score{Score::Straight, hand.back(), hand.at(3)}};
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

FaceValueTypeVector::const_iterator
FindPattern(FaceValueTypeVector::const_iterator begin,
            FaceValueTypeVector::const_iterator end,
            FaceValueTypeVector::const_iterator pbegin,
            FaceValueTypeVector::const_iterator pend) {
  auto match = std::search(begin, end, pbegin, pend,
                           [](auto const &value, auto const &pattern_value) {
                             return ((pattern_value == DontCareValue) &&
                                     (pattern_value != 0)) ||
                                    (value == pattern_value);
                           });
  return match;
}
std::optional<Score> GetThreeOfAKind(FaceValueTypeVector const &diff,
                                     std::vector<Card> const &hand) {
  //   Value: 1 1 1  3  4 | 2  3 3 3  4 | 2  3  4 4 4
  //    Diff: 1 0 0 -2 -1 | 2 -1 0 0 -1 | 2 -1 -1 0 0
  // Pattern:   0 0  x  x |    x 0 0  x |    x  x 0 0
  std::vector<FaceValueTypeVector> patterns{
      FaceValueTypeVector{0, 0, DontCareValue, DontCareValue},
      FaceValueTypeVector{0, DontCareValue, DontCareValue, 0},
      FaceValueTypeVector{DontCareValue, DontCareValue, 0, 0}};
  auto match = diff.cend();
  for (auto const &pattern : patterns) {
    auto tmp_match = FindPattern(std::next(diff.cbegin()), diff.cend(),
                                 pattern.cbegin(), pattern.cend());
    if (tmp_match != diff.cend()) {
      match = tmp_match;
    }
  }
  if (match == diff.cend()) {
    return {};
  }
  auto distance = std::distance(diff.cbegin(), match);
  auto card = hand.cbegin();
  std::advance(card, distance);
  return std::optional{Score{Score::ThreeOfAKind, *card}};
}

Card GetCardNotPartOfPair(
    std::vector<Card> hand,
    FaceValueTypeVector::difference_type distance_two_second_high_pair_card,
    FaceValueTypeVector::difference_type distance_two_second_low_pair_card) {
  std::vector<bool> not_part_of_pair{true, true, true, true, true};
  not_part_of_pair[distance_two_second_high_pair_card] = false;
  not_part_of_pair[distance_two_second_high_pair_card - 1] = false;
  not_part_of_pair[distance_two_second_low_pair_card] = false;
  not_part_of_pair[distance_two_second_low_pair_card - 1] = false;
  auto v = std::find(not_part_of_pair.cbegin(), not_part_of_pair.cend(), true);
  auto dist = std::distance(not_part_of_pair.cbegin(), v);
  return hand[dist];
}
std::optional<Score> GetTwoPairs(FaceValueTypeVector const &diff,
                                 std::vector<Card> hand) {
  //   Value: 1 1  2  3  3 | 2  3 3  4 4 | 2 2  4 4  5
  //    Diff: 1 0 -1 -1 -0 | 2 -1 0 -1 0 | 2 0 -2 0 -1
  // Pattern:   0  x  x  0 |    x 0  x 0 |   0  x 0  x
  auto zero_it = std::next(diff.cbegin());
  std::vector<FaceValueTypeVector::const_iterator> zero_iterators;
  while (zero_it != diff.cend()) {
    zero_it = std::find(zero_it, diff.cend(), FaceValueType{0});
    if (zero_it != diff.cend()) {
      zero_iterators.push_back(zero_it++);
    }
  }
  if (zero_iterators.size() != 2) {
    return {};
  }
  auto distance = std::distance(zero_iterators.front(), zero_iterators.back());
  if (distance == 1) {
    return {};
  }
  auto high_pair_card = hand.cbegin();
  auto distance_to_high_pair =
      std::distance(diff.cbegin(), zero_iterators.back());
  std::advance(high_pair_card, distance_to_high_pair);
  auto low_pair_card = hand.cbegin();
  auto distance_to_low_pair =
      std::distance(diff.cbegin(), zero_iterators.front());
  std::advance(low_pair_card, distance_to_low_pair);

  Score score{Score::TwoPairs};
  score.AddNextTieBreaker(*high_pair_card);
  score.AddNextTieBreaker(*low_pair_card);
  score.AddNextTieBreaker(
      GetCardNotPartOfPair(hand, distance_to_high_pair, distance_to_low_pair));
  return score;
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
  auto three_of_a_kind = GetThreeOfAKind(diff, hand);
  if (three_of_a_kind) {
    return three_of_a_kind.value();
  }
  auto pairs = GetTwoPairs(diff, hand);
  if (pairs) {
    return pairs.value();
  }
  auto pair = GetPair(zeros, diff, hand);
  if (pair) {
    return pair.value();
  }
  return Score(Score::HighCard, hand.crbegin(), hand.crend());
}

bool operator<(const Hand &lhs, const Hand &rhs) {
  auto lhs_score = lhs.GetMostValuableScore();
  auto rhs_score = rhs.GetMostValuableScore();
  return lhs_score < rhs_score;
}
std::ostream &operator<<(std::ostream &os, const Hand &obj) {
  for (auto const &o : obj.hand) {
    os << o << "; ";
  }
  return os;
}
} // namespace pocker