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
  auto flush = GetFlush();
  auto straight = GetStraight();
  if (flush && straight) {
    auto high_card = flush.value().GetTieBreakers().front();
    if (high_card.face_value == Ace) {
      return Score{Score::RoyalFlush, high_card};
    }
    return Score{Score::StraightFlush, high_card};
  }
  auto four_of_a_kind = GetFourOfAKind();
  if (four_of_a_kind) {
    return four_of_a_kind.value();
  }
  auto full_house = GetFullHouse();
  if (full_house) {
    return full_house.value();
  }
  if (flush) {
    return flush.value();
  }
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
  auto const second_cards_of_pairs = GetSecondCardOfPairs();
  if (second_cards_of_pairs.size() != 3) {
    return {};
  }

  auto const third_card = std::next(second_cards_of_pairs.front());
  auto const fourth_card = std::next(third_card);
  if ((third_card != second_cards_of_pairs.at(1)) ||
      (fourth_card != second_cards_of_pairs.at(2))) {
    return {};
  }

  return std::optional{
      Score{Score::FourOfAKind, *second_cards_of_pairs.front()}};
}

std::optional<Score> Hand::GetFullHouse() const {
  auto second_cards_of_pairs = GetSecondCardOfPairs();
  if (second_cards_of_pairs.size() != 3) {
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

std::optional<Score> Hand::GetTwoPairs() const {
  //   Value: 1 1  2  3  3 | 2  3 3  4 4 | 2 2  4 4  5
  //    Diff: 1 0 -1 -1 -0 | 2 -1 0 -1 0 | 2 0 -2 0 -1
  // Pattern:   0  x  x  0 |    x 0  x 0 |   0  x 0  x

  auto zero_iterators = GetSecondCardOfPairs();
  if (zero_iterators.size() != 2) {
    return {};
  }
  if (std::next(zero_iterators.front()) == zero_iterators.back()) {
    return {};
  }
  auto high_pair_card = *zero_iterators.back();
  auto low_pair_card = *zero_iterators.front();
  auto not_pair_cards = GetCardsNotPartOfPair(zero_iterators);

  Score score{Score::TwoPairs};
  score.AddNextTieBreaker(high_pair_card);
  score.AddNextTieBreaker(low_pair_card);
  score.AddNextTieBreaker(not_pair_cards.front());
  return score;
}

std::optional<Score> Hand::GetPair() const {
  auto const zero_iterators = GetSecondCardOfPairs();
  if (zero_iterators.size() != 1) {
    return {};
  }
  Score score{Score::OnePair};

  score.AddNextTieBreaker(*zero_iterators.front());

  auto non_pair_cards = GetCardsNotPartOfPair(zero_iterators);
  for (auto it = non_pair_cards.crbegin(); it != non_pair_cards.crend(); ++it) {
    score.AddNextTieBreaker(*it);
  }
  return std::optional{score};
}

std::ostream &operator<<(std::ostream &os, const Hand &obj) {
  for (auto const &o : obj.hand_) {
    os << o << "; ";
  }
  return os;
}

std::vector<std::vector<Card>::const_iterator>
Hand::GetSecondCardOfPairs() const {
  auto zero_it = std::next(face_value_adjacent_diff_.cbegin());
  std::vector<FaceValueTypeVector::const_iterator> zero_iterators;
  while (zero_it != face_value_adjacent_diff_.cend()) {
    zero_it =
        std::find(zero_it, face_value_adjacent_diff_.cend(), FaceValueType{0});
    if (zero_it != face_value_adjacent_diff_.cend()) {
      zero_iterators.push_back(zero_it++);
    }
  }
  std::vector<std::vector<Card>::const_iterator> cards_part_of_pair;
  for (auto const it : zero_iterators) {
    cards_part_of_pair.push_back(GetCardPartOfPair(it));
  }
  return cards_part_of_pair;
}

std::vector<Card> Hand::GetCardsNotPartOfPair(
    std::vector<std::vector<Card>::const_iterator> second_cards_of_pair) const {
  std::vector<Card> non_par_cards;
  std::vector<std::vector<Card>::const_iterator> first_card_of_pair;
  for (auto const v : second_cards_of_pair) {
    first_card_of_pair.push_back(std::prev(v));
  }
  std::vector<std::vector<Card>::const_iterator> cards_of_pairs(
      second_cards_of_pair);
  for (auto const v : first_card_of_pair) {
    cards_of_pairs.push_back(v);
  }
  for (auto it = hand_.cbegin(); it != hand_.cend(); ++it) {
    if (std::all_of(cards_of_pairs.cbegin(), cards_of_pairs.cend(),
                    [it](auto const v) { return it != v; })) {
      non_par_cards.push_back(*it);
    }
  }
  return non_par_cards;
}

std::vector<Card>::const_iterator Hand::GetCardPartOfPair(
    FaceValueTypeVector::const_iterator second_card_of_pair_position) const {
  auto distance = std::distance(face_value_adjacent_diff_.cbegin(),
                                second_card_of_pair_position);
  auto card = hand_.cbegin();
  std::advance(card, distance);
  return card;
}
} // namespace pocker