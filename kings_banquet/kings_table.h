#pragma once

#include <cstdint>
#include <map>
#include <vector>

#include "graph.h"

class KingsTable {
public:
  KingsTable(std::uint64_t const number_of_seats);

  void ArrangeSeating();
  std::uint64_t NthKnightLeftToTheKing(std::uint64_t const n) const;
  std::vector<std::uint64_t> GetSeatingArrangement() const {
    CheckIfSeatingIsArranged();
    return knights_;
  }
  void Debug();

private:
  std::map<std::uint64_t, std::vector<std::uint64_t>>
  FindPossibleNeighbors() const;
  void CheckIfSeatingIsArranged() const;

private:
  std::vector<std::uint64_t> knights_;
  bool seating_arranged_{false};
};
