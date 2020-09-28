#include "graph.h"

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