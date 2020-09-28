#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "graph.h"

namespace {
using namespace ::testing;

TEST(Graph_Leafs, LineGraph) {
  Graph graph{};
  graph.AddVertex(Vertex{1, Vertex::Edges{2}});
  graph.AddVertex(Vertex{2, Vertex::Edges{1, 3}});
  graph.AddVertex(Vertex{3, Vertex::Edges{2}});

  std::vector<Vertex> leafs = graph.Leafs();
  std::vector<Vertex::Name> leaf_names(leafs.size());
  std::transform(leafs.cbegin(), leafs.cend(), leaf_names.begin(),
                 [](Vertex const &v) { return v.GetName(); });
  EXPECT_THAT(leaf_names, UnorderedElementsAre(1, 3));
}
TEST(Graph_DepthFirstSearch, LineGraph) {
  Graph graph{};
  graph.AddVertex(Vertex{1, Vertex::Edges{2}});
  graph.AddVertex(Vertex{2, Vertex::Edges{1, 3}});
  graph.AddVertex(Vertex{3, Vertex::Edges{2}});

  auto path = graph.GetPathFromTo(1, 3);
  EXPECT_THAT(path, Eq(Path{1, 2, 3}));
}
TEST(Graph_Leafs, ComplexGraph) {
  Graph graph{};
  graph.AddVertex(Vertex{1, Vertex::Edges{2, 7, 4}});
  graph.AddVertex(Vertex{2, Vertex::Edges{3, 6}});
  graph.AddVertex(Vertex{3, Vertex::Edges{5, 2}});
  graph.AddVertex(Vertex{4, Vertex::Edges{1}});
  graph.AddVertex(Vertex{5, Vertex::Edges{3}});
  graph.AddVertex(Vertex{6, Vertex::Edges{7, 2}});
  graph.AddVertex(Vertex{7, Vertex::Edges{6, 1}});

  std::vector<Vertex> leafs = graph.Leafs();
  std::vector<Vertex::Name> leaf_names(leafs.size());
  std::transform(leafs.cbegin(), leafs.cend(), leaf_names.begin(),
                 [](Vertex const &v) { return v.GetName(); });
  EXPECT_THAT(leaf_names, UnorderedElementsAre(5, 4));
}
TEST(Graph_DepthFirstSearch, ComplexGraph) {
  Graph graph{};
  graph.AddVertex(Vertex{1, Vertex::Edges{2, 7, 4}});
  graph.AddVertex(Vertex{2, Vertex::Edges{3, 6}});
  graph.AddVertex(Vertex{3, Vertex::Edges{5, 2}});
  graph.AddVertex(Vertex{4, Vertex::Edges{1}});
  graph.AddVertex(Vertex{5, Vertex::Edges{3}});
  graph.AddVertex(Vertex{6, Vertex::Edges{7, 2}});
  graph.AddVertex(Vertex{7, Vertex::Edges{6, 1}});

  auto path = graph.GetPathFromTo(4, 5);
  EXPECT_THAT(path, Eq(Path{4, 1, 7, 6, 2, 3, 5}));
}
TEST(Graph_Leafs, CycleWithAditionalVertex) {
  Graph graph{};
  graph.AddVertex(Vertex{1, Vertex::Edges{2}});
  graph.AddVertex(Vertex{2, Vertex::Edges{1, 3, 4}});
  graph.AddVertex(Vertex{3, Vertex::Edges{2, 4}});
  graph.AddVertex(Vertex{4, Vertex::Edges{3, 2}});

  std::vector<Vertex> leafs = graph.Leafs();
  std::vector<Vertex::Name> leaf_names(leafs.size());
  std::transform(leafs.cbegin(), leafs.cend(), leaf_names.begin(),
                 [](Vertex const &v) { return v.GetName(); });
  EXPECT_THAT(leaf_names, UnorderedElementsAre(1));
}
} // namespace