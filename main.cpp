/* Copyright 2015 Daniel Pade */
#include <iostream>
#include <set>
#include <vector>
#include "./stdafx.h"

typedef TUNGraph::TNodeI TNodeI;
typedef PUNGraph PGraph;  // undirected graph

void dfs(PGraph, TNodeI, std::set<int>*);
void findConnectedComponents(PGraph, std::set<std::set<int>>*);
std::vector<int> nthDegrees(PGraph, TNodeI);

int main(int argc, char* argv[]) {
  // what type of graph do you want to use?
  // typedef PNGraph PGraph;  //   directed graph
  // typedef PNEGraph PGraph;  //   directed multigraph
  // typedef TPt<TNodeNet<TInt> > PGraph;
  // typedef TPt<TNodeEdgeNet<TInt, TInt> > PGraph;

  PGraph amazon_graph =
      TSnap::LoadEdgeList<PUNGraph>("com-amazon.all.dedup.cmty.txt",
                                    0, 1);
  TSnap::PrintInfo(amazon_graph, "Amazon Graph");


  std::set<std::set<int>> components;
  findConnectedComponents(amazon_graph, &components);
  amazon_graph = TSnap::LoadEdgeList<PUNGraph>("com-amazon.all.dedup.cmty.txt",
                                    0, 1);

  std::cout << amazon_graph->GetNodes() << std::endl;

  std::cout << "NodeID 1Deg 2Deg Comp# CompSize" << std::endl;
  int compNo = 0;
  for (std::set<std::set<int>>::iterator it = components.begin();
       it != components.end(); ++it)  {
      std::set<int> component = *it;
      for (std::set<int>::iterator cit = component.begin();
           cit != component.end(); ++cit) {
          int nodeId = *cit;
          TNodeI node = amazon_graph->GetNI(nodeId);
          std::vector<int> degrees = nthDegrees(amazon_graph, node);

          std::cout << nodeId << " ";

          for (unsigned int i = 0; i < degrees.size(); i++) {
              std::cout << degrees.at(i) << " ";
          }
          std::cout << compNo << " ";
          std::cout << component.size();
          std::cout << std::endl;
      }
      compNo++;
  }
}

void findConnectedComponents(PGraph graph,
                             std::set<std::set<int>> *components) {
  TNodeI node_iter = graph->BegNI();
  while (!graph->Empty()) {
      std::set<int> connected;
      dfs(graph, node_iter, &connected);
      for (std::set<int>::iterator it=connected.begin();
           it != connected.end(); ++it) {
          graph->DelNode(*it);
      }
      components->insert(connected);
      node_iter = graph->BegNI();
  }
}

std::vector<int> nthDegrees(PGraph graph, TNodeI node) {
    int first = node.GetDeg();
    int second = first;

    for (int i = 0; i < first; i++) {
        int nbrId = node.GetOutNId(i);
        TNodeI nbr = graph->GetNI(nbrId);
        second += nbr.GetDeg() - 1;
    }
    return std::vector<int>({first, second});
}

void dfs(PGraph graph, TNodeI node, std::set<int> *result) {
    result->insert(node.GetId());
    bool success = true;
    for (int i = 0; i < node.GetOutDeg(); i++) {
        unsigned int prevSize = result->size();

        int nbrId = node.GetOutNId(i);
        TNodeI nbr = graph->GetNI(nbrId);
        result->insert(nbrId);

        success = success && (prevSize == result->size());
        if (success) {
            dfs(graph, nbr, result);
        }
    }
}
