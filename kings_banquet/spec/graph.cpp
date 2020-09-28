#include "graph.h"

std::optional<Vertex::Name> JumpBack(std::vector<Vertices::iterator> &path);
Path ConvertToNames(std::vector<Vertices::iterator> const &path);
void AddIfNotInPath(std::vector<Vertices::iterator> &path,
                    Vertices::iterator const next);

Path Graph::GetPathFromTo(Vertex::Name start, Vertex::Name end) {

  auto vertex_start = FindVertexByName(start);
  if (vertex_start == vertices.end()) {
    return {};
  }
  auto vertex_end = FindVertexByName(end);
  if (vertex_end == vertices.end()) {
    return {};
  }

  return DepthFirstSearchUntilPathWithAllVerticesVisitedFound(vertex_start,
                                                              vertex_end);
}
Vertices Graph::Leafs() const {
  Vertices leafs{};
  std::copy_if(vertices.cbegin(), vertices.cend(), std::back_inserter(leafs),
               [](Vertex const &v) { return v.NumberOfEdges() < 2; });
  return leafs;
}
Vertices::iterator Graph::FindVertexByName(Vertex::Name name) {
  auto vertex =
      std::find_if(vertices.begin(), vertices.end(),
                   [name](Vertex const &v) { return v.GetName() == name; });
  return vertex;
}

Path Graph::DepthFirstSearchUntilPathWithAllVerticesVisitedFound(
    Vertices::iterator start, Vertices::iterator end) {
  std::vector<Vertices::iterator> path{start};
  auto next = start->Next();
  while (next) {
    Vertex::Name next_value = next.value();
    auto next_vertex = FindVertexByName(next_value);

    AddIfNotInPath(path, next_vertex);

    if (next_vertex == end) {
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
std::optional<Vertex::Name> JumpBack(std::vector<Vertices::iterator> &path) {
  auto next = path.back()->Next();
  while (!next) {
    path.back()->ClearVisitedCounter();
    path.pop_back();
    if (path.empty()) {
      return {};
    }
    next = path.back()->Next();
  }
  return next;
}

Path ConvertToNames(std::vector<Vertices::iterator> const &path) {
  Path name_path(path.size());
  std::transform(path.cbegin(), path.cend(), name_path.begin(),
                 [](Vertices::iterator v) { return v->GetName(); });
  return name_path;
}

void AddIfNotInPath(std::vector<Vertices::iterator> &path,
                    Vertices::iterator const next) {
  if (std::find(path.cbegin(), path.cend(), next) == path.cend()) {
    path.push_back(next);
  }
}
