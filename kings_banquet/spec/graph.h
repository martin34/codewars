#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <optional>
#include <vector>
// #include <iostream>

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
std::optional<Vertex::Name> JumpBack(std::vector<Vertices::iterator> &path);
using Path = std::vector<Vertex::Name>;
Path ConvertToNames(std::vector<Vertices::iterator> const &path);

class Graph {
public:
  void AddVertex(const Vertex &vertex) { vertices.push_back(vertex); }
  Vertices Leafs() {
    Vertices leafs{};
    std::copy_if(vertices.cbegin(), vertices.cend(), std::back_inserter(leafs),
                 [](Vertex const &v) { return v.NumberOfEdges() < 2; });
    return leafs;
  }
  Path GetPathFromTo(Vertex::Name start, Vertex::Name end) {

    auto vertex_start = FindVertexByName(start);
    if (vertex_start == vertices.end()) {
      return {};
    }
    auto vertex_end = FindVertexByName(end);
    if (vertex_end == vertices.end()) {
      return {};
    }

    std::vector<Vertices::iterator> path{};
    path.push_back(vertex_start);
    auto next = vertex_start->Next();
    while (next) {
      Vertex::Name next_value = next.value();
      auto next_vertex = FindVertexByName(next_value);
      // Ignore, when already visited
      if (std::find(path.cbegin(), path.cend(), next_vertex) == path.cend()) {
        path.push_back(next_vertex);
      }
      if (next_vertex->GetName() == end) {
        if (path.size() == vertices.size()) {
          return ConvertToNames(path);

        } else {
          path.back()->ClearVisitedCounter();
          path.pop_back();
        }
      }
      next = JumpBack(path);
    }
    return {};
  }

private:
  Vertices::iterator FindVertexByName(Vertex::Name name) {
    auto vertex =
        std::find_if(vertices.begin(), vertices.end(),
                     [name](Vertex const &v) { return v.GetName() == name; });
    return vertex;
  }
  Vertices vertices{};
};