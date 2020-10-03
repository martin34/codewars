#include "kings_table.h"

#include <algorithm>
#include <map>
#include <numeric>

#include "fibonacci.h"
#include "graph.h"

Graph BuildGraphFromNeighbors(
    std::map<std::uint64_t, std::vector<std::uint64_t>> &neighbors);

KingsTable::KingsTable(std::uint64_t const number_of_seats)
    : knights_(number_of_seats) {
  std::iota(knights_.begin(), knights_.end(), 1);
}

void KingsTable::ArrangeSeating() {
  auto neighbors = FindPossibleNeighbors();

  auto graph = BuildGraphFromNeighbors(neighbors);

  auto leafs = graph.Leafs();
  std::sort(
      leafs.begin(), leafs.end(),
      [](Vertex const &lhs, Vertex const &rhs) { return lhs.name < rhs.name; });
  if (leafs.size() != 2) {
    throw std::runtime_error("To many knights need to be beside the king");
  }
  auto seating_order = graph.GetPathFromTo(leafs.at(0).name, leafs.at(1).name);
  if (seating_order.empty()) {
    throw std::runtime_error("Did not find a solution");
  }
  knights_ = seating_order;
  seating_arranged_ = true;
}
std::uint64_t KingsTable::NthKnightLeftToTheKing(std::uint64_t const n) const {
  if (n > knights_.size()) {
    throw std::runtime_error{"Not enough seats"};
  }

  CheckIfSeatingIsArranged();

  return knights_[n - 1];
}

Graph BuildGraphFromNeighbors(
    std::map<std::uint64_t, std::vector<std::uint64_t>> &neighbors) {
  for (std::uint64_t i = 1; i <= static_cast<std::uint64_t>(neighbors.size());
       ++i) {
    for (auto &e : neighbors[i]) {
      if (e > i) {
        neighbors[e].push_back(i);
      }
    }
  }
  Graph graph{};
  for (auto const &vertex : neighbors) {
    graph.AddVertex(Vertex{vertex.first, vertex.second});
  }
  return graph;
}
std::map<std::uint64_t, std::vector<std::uint64_t>>
KingsTable::FindPossibleNeighbors() const {
  // Create pairs/s
  if (knights_.size() < 2) {
    return {};
  }
  std::map<std::uint64_t, std::vector<std::uint64_t>> neighbors{};
  auto first = knights_.cbegin();
  auto const end = knights_.cend();
  for (; first != std::prev(end); ++first) {
    std::vector<std::uint64_t> neighbors_of_first{};
    auto second = std::next(first);
    for (; second != end; ++second) {
      // Sum
      auto const sum = *first + *second;
      // Keep if Fibonacci
      if (IsAFibonacciNumber(sum)) {
        neighbors_of_first.push_back(*second);
      }
    }
    neighbors.emplace(std::make_pair(*first, neighbors_of_first));
  }
  return neighbors;
}

void KingsTable::CheckIfSeatingIsArranged() const {
  if (!seating_arranged_) {
    throw std::runtime_error{"Seating not arranged --> call ArrangeSeating"};
  }
}
