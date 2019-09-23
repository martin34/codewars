#include <algorithm>
#include <iterator>
#include <numeric>
#include <set>

#include "hand.h"

namespace pocker {

using FaceValueType = Hand::FaceValueType;
using FaceValueTypeVector = Hand::FaceValueTypeVector;
constexpr FaceValueType DontCareValue =
    std::numeric_limits<FaceValueType>::max();

Hand::Hand(Card c0, Card c1, Card c2, Card c3, Card c4)
    : hand_{c0, c1, c2, c3, c4} {
  std::sort(hand_.begin(), hand_.end(), [](Card const &lhs, Card const &rhs) {
    return lhs.face_value < rhs.face_value;
  });

  FaceValueTypeVector face_values;
  std::transform(hand_.cbegin(), hand_.cend(), std::back_inserter(face_values),
                 [](auto const &card) { return card.face_value; });

  std::adjacent_difference(face_values.cbegin(), face_values.cend(),
                           std::back_inserter(face_value_adjacent_diff_));
}

Score Hand::GetMostValuableScore() const {
  auto four_of_a_kind = GetFourOfAKind();
  if (four_of_a_kind) {
    return four_of_a_kind.value();
  }
  auto full_house = GetFullHouse();
  if (full_house) {
    return full_house.value();
  }
  auto flush = GetFlush();
  if (flush) {
    return flush.value();
  }
  auto straight = GetStraight();
  if (straight) {
    return straight.value();
  }
  auto three_of_a_kind = GetThreeOfAKind();
  if (three_of_a_kind) {
    return three_of_a_kind.value();
  }
  auto pairs = GetTwoPairs();
  if (pairs) {
    return pairs.value();
  }
  auto pair = GetPair();
  if (pair) {
    return pair.value();
  }
  return Score(Score::HighCard, hand_.crbegin(), hand_.crend());
}

bool operator<(const Hand &lhs, const Hand &rhs) {
  auto lhs_score = lhs.GetMostValuableScore();
  auto rhs_score = rhs.GetMostValuableScore();
  return lhs_score < rhs_score;
}

std::optional<Score> Hand::GetFlush() const {
  std::set<SuitType> suit_values;
  std::transform(hand_.cbegin(), hand_.cend(),
                 std::inserter(suit_values, suit_values.begin()),
                 [](auto v) { return v.suit; });
  if (suit_values.size() == 1) {
    return Score{Score::Flush, hand_.back()};
  }
  return {};
}

std::optional<Score> Hand::GetStraight() const {
  auto ones = std::count(std::next(face_value_adjacent_diff_.cbegin()),
                         face_value_adjacent_diff_.cend(),
                         std::underlying_type<FaceValue>::type{1});
  if (ones == 4) {
    return std::optional{Score{Score::Straight, hand_.back(), hand_.at(3)}};
  }
  return {};
}

std::optional<Score> Hand::GetFourOfAKind() const {
  auto second_card_of_pair_positions = GetSecondCardOfPairPositions();
  if (second_card_of_pair_positions.size() != 3) {
    return {};
  }
  std::vector<FaceValueTypeVector::difference_type> distance_between_pairs;
  auto first = second_card_of_pair_positions.cbegin();
  auto second = std::next(second_card_of_pair_positions.cbegin());
  for (; first != second_card_of_pair_positions.cend() &&
         second != second_card_of_pair_positions.cend();
       ++first, ++second) {
    distance_between_pairs.push_back(std::distance(*first, *second));
  }
  if ((distance_between_pairs.front() != 1) ||
      (distance_between_pairs.back() != 1)) {
    return {};
  }

  auto distance = std::distance(face_value_adjacent_diff_.cbegin(),
                                second_card_of_pair_positions.front());
  auto card = hand_.cbegin();
  std::advance(card, distance);
  return std::optional{Score{Score::FourOfAKind, *card}};
}

std::optional<Score> Hand::GetFullHouse() const {
  auto second_card_of_pair_positions = GetSecondCardOfPairPositions();
  if (second_card_of_pair_positions.size() != 3) {
    return {};
  }
  auto three_of_a_kind = GetThreeOfAKind();
  if (!three_of_a_kind) {
    return {};
  }
  return std::optional{Score{Score::FullHouse,
                             three_of_a_kind.value().GetTieBreakers().front()}};
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
std::optional<Score> Hand::GetThreeOfAKind() const {
  //   Value: 1 1 1  3  4 | 2  3 3 3  4 | 2  3  4 4 4
  //    Diff: 1 0 0 -2 -1 | 2 -1 0 0 -1 | 2 -1 -1 0 0
  // Pattern:   0 0  x  x |    x 0 0  x |    x  x 0 0
  std::vector<FaceValueTypeVector> patterns{
      FaceValueTypeVector{0, 0, DontCareValue, DontCareValue},
      FaceValueTypeVector{0, DontCareValue, DontCareValue, 0},
      FaceValueTypeVector{DontCareValue, DontCareValue, 0, 0}};
  auto match = face_value_adjacent_diff_.cend();
  for (auto const &pattern : patterns) {
    auto tmp_match = FindPattern(std::next(face_value_adjacent_diff_.cbegin()),
                                 face_value_adjacent_diff_.cend(),
                                 pattern.cbegin(), pattern.cend());
    if (tmp_match != face_value_adjacent_diff_.cend()) {
      match = tmp_match;
    }
  }
  if (match == face_value_adjacent_diff_.cend()) {
    return {};
  }
  auto distance = std::distance(face_value_adjacent_diff_.cbegin(), match);
  auto card = hand_.cbegin();
  std::advance(card, distance);
  return std::optional{Score{Score::ThreeOfAKind, *card}};
}

Card GetCardNotPartOfPair(
    std::vector<Card> const &hand,
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

std::optional<Score> Hand::GetTwoPairs() const {
  //   Value: 1 1  2  3  3 | 2  3 3  4 4 | 2 2  4 4  5
  //    Diff: 1 0 -1 -1 -0 | 2 -1 0 -1 0 | 2 0 -2 0 -1
  // Pattern:   0  x  x  0 |    x 0  x 0 |   0  x 0  x

  auto zero_iterators = GetSecondCardOfPairPositions();
  if (zero_iterators.size() != 2) {
    return {};
  }
  auto distance = std::distance(zero_iterators.front(), zero_iterators.back());
  if (distance == 1) {
    return {};
  }
  auto high_pair_card = hand_.cbegin();
  auto distance_to_high_pair =
      std::distance(face_value_adjacent_diff_.cbegin(), zero_iterators.back());
  std::advance(high_pair_card, distance_to_high_pair);
  auto low_pair_card = hand_.cbegin();
  auto distance_to_low_pair =
      std::distance(face_value_adjacent_diff_.cbegin(), zero_iterators.front());
  std::advance(low_pair_card, distance_to_low_pair);

  Score score{Score::TwoPairs};
  score.AddNextTieBreaker(*high_pair_card);
  score.AddNextTieBreaker(*low_pair_card);
  score.AddNextTieBreaker(
      GetCardNotPartOfPair(hand_, distance_to_high_pair, distance_to_low_pair));
  return score;
}

std::optional<Score> Hand::GetPair() const {

  auto zeros = std::count(std::next(face_value_adjacent_diff_.cbegin()),
                          face_value_adjacent_diff_.cend(),
                          std::underlying_type<FaceValue>::type{0});
  if (zeros != 1) {
    return {};
  }
  auto position_with_card = std::find(face_value_adjacent_diff_.cbegin(),
                                      face_value_adjacent_diff_.cend(), 0);
  auto distance =
      std::distance(face_value_adjacent_diff_.cbegin(), position_with_card);
  auto card = hand_.cbegin();
  std::advance(card, distance);
  return std::optional{Score{Score::OnePair, *card}};
}
std::ostream &operator<<(std::ostream &os, const Hand &obj) {
  for (auto const &o : obj.hand_) {
    os << o << "; ";
  }
  return os;
}

std::vector<FaceValueTypeVector::const_iterator>
Hand::GetSecondCardOfPairPositions() const {
  auto zero_it = std::next(face_value_adjacent_diff_.cbegin());
  std::vector<FaceValueTypeVector::const_iterator> zero_iterators;
  while (zero_it != face_value_adjacent_diff_.cend()) {
    zero_it =
        std::find(zero_it, face_value_adjacent_diff_.cend(), FaceValueType{0});
    if (zero_it != face_value_adjacent_diff_.cend()) {
      zero_iterators.push_back(zero_it++);
    }
  }
  return zero_iterators;
}
} // namespace pocker