/* Copyright 2015 Daniel Pade */
#include <iostream>
#include <set>
#include "./stdafx.h"

void visit_node(int, std::set<int>*, std::set<int>*);

int main(int argc, char* argv[]) {
  // what type of graph do you want to use?
  typedef PUNGraph PGraph;  // undirected graph
  typedef TUNGraph::TNodeI TNodeI;
  // typedef PNGraph PGraph;  //   directed graph
  // typedef PNEGraph PGraph;  //   directed multigraph
  // typedef TPt<TNodeNet<TInt> > PGraph;
  // typedef TPt<TNodeEdgeNet<TInt, TInt> > PGraph;

  PGraph amazon_graph =
      TSnap::LoadEdgeList<PUNGraph>("com-amazon.all.dedup.cmty.txt",
                                    0, 1);
  TSnap::PrintInfo(amazon_graph, "Amazon Graph");

  // Build a small subset of the amazon graph
  PGraph small_graph = PGraph::New();
  TNodeI node_iter = amazon_graph->BegNI();

  std::set<int> visited_nodes;
  std::set<int> connected_nodes;

  visit_node(node_iter.GetId(), &visited_nodes, &connected_nodes);

  while (small_graph->GetNodes() < 100 && connected_nodes.size() > 0) {
      TNodeI node = amazon_graph->GetNI(*connected_nodes.begin());
      connected_nodes.erase(connected_nodes.begin());
      int cur_id = node.GetId();

      if (!small_graph->IsNode(cur_id)) {
          small_graph->AddNode(cur_id);
      }

      for (int index = 0; index < node.GetDeg(); index++) {
          int neighb_id = node.GetNbrNId(index);
          if (!small_graph->IsNode(neighb_id)) {
              small_graph->AddNode(neighb_id);
          }
          small_graph->AddEdge(cur_id, neighb_id);

          // if neighb_id is not in visited_nodes
          if (visited_nodes.find(neighb_id) == visited_nodes.end()) {
              visit_node(neighb_id, &visited_nodes, &connected_nodes);
          }
      }
      // Throw in a random node
      int random_id = amazon_graph->GetRndNId();
      // if random_id is not in visited_nodes
      if (visited_nodes.find(random_id) == visited_nodes.end()) {
          visit_node(random_id, &visited_nodes, &connected_nodes);
      }
  }
  std::cout << std::endl;
  TSnap::PrintInfo(small_graph, "Small Graph");
  TSnap::DrawGViz(small_graph, TGVizLayout::gvlDot,
                  "small_graph.png", "Amazon Graph Subset");
}

void visit_node(int id, std::set<int> *visited, std::set<int> *connected) {
    visited->insert(id);
    connected->insert(id);
}
