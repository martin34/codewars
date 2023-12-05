#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <optional>
#include <vector>

struct Vertex {
  using Name = std::uint64_t;
  using Edges = std::vector<Name>;

  Name name;
  Edges edges;
};
using Vertices = std::vector<Vertex>;
using Path = std::vector<Vertex::Name>;

class Graph {
public:
  void AddVertex(const Vertex &vertex) { vertices.push_back(vertex); }
  Vertices Leafs() const;
  Path GetPathFromTo(Vertex::Name start, Vertex::Name end);

  void Print() const;

private:
  Vertices vertices{};
};
