#pragma once

#include <optional>
#include <ostream>

namespace pocker {

enum FaceValue : std::int32_t {
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King,
  Ace
};
std::ostream &operator<<(std::ostream &os, const FaceValue &p);

enum Suit { Heart, Tile, Clover, Pike };
std::ostream &operator<<(std::ostream &os, const Suit &p);

struct Card {
  Card(Suit suit, FaceValue face_value) : suit(suit), face_value(face_value) {}
  Suit suit;
  FaceValue face_value;
};
std::ostream &operator<<(std::ostream &os, const Card &p);

} // namespace pocker