#ifndef WGRAPH_H
#define WGRAPH_H

#include <iostream>
#include <limits>
#include <fstream>
#include <set>
#include <sstream>

//a weighted, undirected WGraph implemented with adjacency matrix
//fixed size

typedef unsigned int VertexID; // unsigned == 0 to 255, no negative numbers

class WGraph{
public: 
  WGraph();
  WGraph(unsigned int sz);
  ~WGraph();
  void addEdge(VertexID i, VertexID j, double w);
  void removeEdge(VertexID i, VertexID j);
  bool areAdjacent(VertexID i, VertexID j);
  double cheapestCost(VertexID i, VertexID j);
  void calcFW();
  void printGraph();
  void computeMST();

private:
  double** m_adj; //is there an edge between two vertices and what's the weight of the edge
  double** m_conn; //more general, is there a path between a start and a finish and what's the cost (all parts summed)
  unsigned int m_size; //nodes in WGraph (fixed)

};

#endif