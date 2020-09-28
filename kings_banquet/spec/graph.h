#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <optional>
#include <vector>

class Vertex {
public:
  using Name = std::uint64_t;
  using Edges = std::vector<Name>;
  Vertex(Name const name, Edges edges) : name_{name}, edges_{edges} {
    std::sort(edges_.begin(), edges_.end());
  }
  Name GetName() const { return name_; }
  std::uint64_t NumberOfEdges() const {
    return static_cast<std::uint64_t>(edges_.size());
  }

  std::optional<Name> Next() {
    if (visited < edges_.size()) {
      auto tmp = visited;
      ++visited;
      return {edges_.at(tmp)};
    } else {
      return {};
    }
  }
  void ClearVisitedCounter() { visited = std::size_t{0}; }

  Name name_;
  Edges edges_;
  std::size_t visited{0};
};

using Vertices = std::vector<Vertex>;
using Path = std::vector<Vertex::Name>;

class Graph {
public:
  void AddVertex(const Vertex &vertex) { vertices.push_back(vertex); }
  Vertices Leafs() const;
  Path GetPathFromTo(Vertex::Name start, Vertex::Name end);

private:
  Path
  DepthFirstSearchUntilPathWithAllVerticesVisitedFound(Vertices::iterator start,
                                                       Vertices::iterator end);
  Vertices::iterator FindVertexByName(Vertex::Name name);

  Vertices vertices{};
};