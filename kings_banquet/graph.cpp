#include "graph.h"
#include <iostream>

class VisitableVertex {
public:
  VisitableVertex() {}
  explicit VisitableVertex(Vertex::Name name, Vertex::Edges edges)
      : name_{name}, edges_{edges} {
    std::sort(edges_.begin(), edges_.end());
  }
  explicit VisitableVertex(Vertex vertex)
      : VisitableVertex{vertex.name, vertex.edges} {}

  static VisitableVertex CreateVisitableVertex(Vertex vertex) {
    VisitableVertex v{vertex};
    return v;
  }
  Vertex::Name GetName() const { return name_; }
  std::uint64_t NumberOfEdges() const {
    return static_cast<std::uint64_t>(edges_.size());
  }

  std::optional<Vertex::Name> Next() {
    if (visited < edges_.size()) {
      auto tmp = visited;
      ++visited;
      return {edges_.at(tmp)};
    } else {
      return {};
    }
  }
  void ClearVisitedCounter() { visited = std::size_t{0}; }

  Vertex::Name name_{};
  Vertex::Edges edges_{};
  std::size_t visited{0};
};
using VisitableVertices = std::vector<VisitableVertex>;

VisitableVertices::iterator FindVertexByName(VisitableVertices &vertices,
                                             Vertex::Name name) {
  auto vertex = std::find_if(
      vertices.begin(), vertices.end(),
      [name](VisitableVertex const &v) { return v.GetName() == name; });
  return vertex;
}

std::optional<Vertex::Name>
JumpBackIfNoSuccessor(std::vector<VisitableVertices::iterator> &path);
Path ConvertToNames(std::vector<VisitableVertices::iterator> const &path);
void AddIfNotInPath(std::vector<VisitableVertices::iterator> &path,
                    VisitableVertices::iterator const next);
Path DepthFirstSearchUntilPathWithAllVerticesVisitedFound(
    VisitableVertices &visitable, VisitableVertices::iterator start,
    VisitableVertices::iterator end);

Vertices Graph::Leafs() const {
  Vertices leafs{};
  std::copy_if(vertices.cbegin(), vertices.cend(), std::back_inserter(leafs),
               [](Vertex const &v) { return v.edges.size() < 2; });
  return leafs;
}

Path Graph::GetPathFromTo(Vertex::Name start, Vertex::Name end) {

  VisitableVertices visitable(vertices.size());
  std::transform(vertices.cbegin(), vertices.cend(), visitable.begin(),
                 [](Vertex vertex) {
                   return VisitableVertex::CreateVisitableVertex(vertex);
                 });

  auto vertex_start = FindVertexByName(visitable, start);
  if (vertex_start == visitable.end()) {
    return {};
  }
  auto vertex_end = FindVertexByName(visitable, end);
  if (vertex_end == visitable.end()) {
    return {};
  }

  return DepthFirstSearchUntilPathWithAllVerticesVisitedFound(
      visitable, vertex_start, vertex_end);
}

Path DepthFirstSearchUntilPathWithAllVerticesVisitedFound(
    VisitableVertices &visitable, VisitableVertices::iterator start,
    VisitableVertices::iterator end) {
  std::vector<VisitableVertices::iterator> path{start};
  auto next = start->Next();
  while (next) {
    Vertex::Name next_value = next.value();
    // std::cout << next_value << " ";
    auto next_vertex = FindVertexByName(visitable, next_value);

    AddIfNotInPath(path, next_vertex);

    if (next_vertex == end) {
      if (path.size() == visitable.size()) {
        return ConvertToNames(path);
      } else {
        path.back()->ClearVisitedCounter();
        path.pop_back();
      }
    }
    next = JumpBackIfNoSuccessor(path);
  }
  return {};
}
std::optional<Vertex::Name>
JumpBackIfNoSuccessor(std::vector<VisitableVertices::iterator> &path) {
  auto next = path.back()->Next();
  while (!next) {
    path.back()->ClearVisitedCounter();
    path.pop_back();
    if (path.empty()) {
      return {};
    }
    // std::cout << " < ";
    next = path.back()->Next();
  }
  return next;
}

Path ConvertToNames(std::vector<VisitableVertices::iterator> const &path) {
  Path name_path(path.size());
  std::transform(path.cbegin(), path.cend(), name_path.begin(),
                 [](VisitableVertices::iterator v) { return v->GetName(); });
  return name_path;
}

void AddIfNotInPath(std::vector<VisitableVertices::iterator> &path,
                    VisitableVertices::iterator const next) {
  if (std::find(path.cbegin(), path.cend(), next) == path.cend()) {
    path.push_back(next);
  }
}

void Graph::Print() const {
  for (const auto &v : vertices) {
    std::cout << v.name;
    for (const auto e : v.edges) {
      std::cout << "," << e;
    }
    std::cout << std::endl;
  }
}
