#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <optional>
#include <vector>
// #include <iostream>

class Vertex {
public:
  using Name = std::int32_t;
  using Edges = std::vector<Name>;
  Vertex(Name const name, Edges edges) : name_{name}, edges_{edges} {
    std::sort(edges_.begin(), edges_.end());
  }
  Name GetName() const { return name_; }
  std::int32_t NumberOfEdges() const {
    return static_cast<std::int32_t>(edges_.size());
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

class Graph {
public:
  using Vertices = std::vector<Vertex>;
  using Path = std::vector<Vertex::Name>;
  void AddVertex(const Vertex &vertex) { vertices.push_back(vertex); }
  Vertices Leafs() {
    Vertices leafs{};
    std::copy_if(vertices.cbegin(), vertices.cend(), std::back_inserter(leafs),
                 [](Vertex const &v) { return v.NumberOfEdges() < 2; });
    return leafs;
  }
  Path GetPathFromTo(Vertex::Name start, Vertex::Name end) {
    auto vertex_start =
        std::find_if(vertices.begin(), vertices.end(),
                     [start](Vertex const &v) { return v.GetName() == start; });
    if (vertex_start == vertices.end()) {
      return {};
    }
    std::vector<Vertices::iterator> path{};
    path.push_back(vertex_start);
    auto next = vertex_start->Next();
    while (next) {
      Vertex::Name next_value = next.value();
      //   std::cerr << "Next: " << next_value << '\n';
      auto next_vertex = std::find_if(
          vertices.begin(), vertices.end(),
          [next_value](Vertex const &v) { return v.GetName() == next_value; });
      // Ignore, when already visited
      if (std::find(path.cbegin(), path.cend(), next_vertex) == path.cend()) {
        path.push_back(next_vertex);
        // std::cerr << "Path: ";
        // for(auto v : path)
        // {
        //     std::cerr << " " << v->GetName();
        // }
        // std::cerr << '\n';
      }
      if (next_vertex->GetName() == end) {
        if (path.size() == vertices.size()) {
          Path name_path(path.size());
          std::transform(path.cbegin(), path.cend(), name_path.begin(),
                         [](Vertices::iterator v) { return v->GetName(); });
          return name_path;
        } else {
          path.back()->ClearVisitedCounter();
          path.pop_back();
        }
      }
      next = path.back()->Next();
      while (!next) {
        path.back()->ClearVisitedCounter();
        path.pop_back();
        if (path.empty()) {
          return {};
        }
        auto name = path.back()->GetName();
        auto next_vertex = std::find_if(
            vertices.begin(), vertices.end(),
            [name](Vertex const &v) { return v.GetName() == name; });
        next = next_vertex->Next();
      }
    }
    return {};
  }

private:
  Vertices vertices{};
};