#include "pocker/parser.h"

#include <string>
#include <vector>

#include "utils/string/split.h"

namespace pocker {
Suit ParseSuit(char v);
FaceValue ParseFaceValue(char v);

std::pair<Hand, Hand> ParseHandsFromLine(std::string const &line) {
  auto string_cards = utils::Split(line);
  std::vector<Card> cards;
  for (auto const &card : string_cards) {
    auto suit = ParseSuit(card[1]);
    auto face_value = ParseFaceValue(card[0]);
    cards.push_back({suit, face_value});
  }
  return {Hand{cards[0], cards[1], cards[2], cards[3], cards[4]},
          Hand{cards[5], cards[6], cards[7], cards[8], cards[9]}};
}

Suit ParseSuit(char v) {
  switch (v) {
  case 'H':
    return Heart;
  case 'C':
    return Clover;
  case 'D':
    return Tile;
  case 'S':
    return Pike;
  }
  throw std::logic_error("Can't parse Suit from " + v);
}
FaceValue ParseFaceValue(char v) {
  switch (v) {
  case '2':
    return Two;
  case '3':
    return Three;
  case '4':
    return Four;
  case '5':
    return Five;
  case '6':
    return Six;
  case '7':
    return Seven;
  case '8':
    return Eight;
  case '9':
    return Nine;
  case 'T':
    return Ten;
  case 'J':
    return Jack;
  case 'Q':
    return Queen;
  case 'K':
    return King;
  case 'A':
    return Ace;
  }
  throw std::logic_error("Can't parse FaceValue from " + v);
}

} // namespace pocker