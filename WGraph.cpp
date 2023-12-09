#include "WGraph.h"
#include <iostream>

using namespace std;

WGraph::WGraph(){
  m_size = 0;
  m_adj = NULL;
  m_conn = NULL;
}

WGraph::WGraph(unsigned int sz){
  m_size = sz;
  //allocate sz * sz adj matrix
  m_adj = new double*[sz];
  m_conn = new double*[sz];
  for(int i = 0; i < m_size; ++i){
    m_adj[i] = new double[sz];
    m_conn[i] = new double[sz];
  }
  //start with edges
  for(int i = 0; i < m_size; ++i){
    for(int j = 0; j < m_size; ++j){
      m_adj[i][j] = std::numeric_limits<double>::max(); //essentially infinity
      m_conn[i][j] = std::numeric_limits<double>::max();
    }
  }
}

WGraph::~WGraph(){
  //release memory
}

void WGraph::addEdge(VertexID i, VertexID j, double w){
  if(i < m_size && j < m_size){
    m_adj[i][j] = w;
    m_adj[j][i] = w;
  }
}

void WGraph::removeEdge(VertexID i, VertexID j){
  if(i < m_size && j < m_size){
    m_adj[i][j] = std::numeric_limits<double>::max();
    m_adj[j][i] = std::numeric_limits<double>::max();
  }
}

bool WGraph::areAdjacent(VertexID i, VertexID j){
  return (m_adj[i][j] < std::numeric_limits<double>::max());
}


// Floyd - Worshol: Good for relatively stable graphs
void WGraph::calcFW(){ //runtime complexity O(v^3)
  for(int i = 0; i < m_size; ++i){
    for(int j = 0; j < m_size; ++j){
      m_conn[i][j] = m_adj[i][j]; //start with conn == adj matrix
    }
  }
  for(int im = 0; im < m_size; ++ im){ //intermediate points --> transitive closure
    for(int source = 0; source < m_size; ++source){ //source = starting point
      for(int sink = 0; sink <m_size; ++sink){ //sink = ending point
        if(source == sink){
          continue;
        }else if(m_conn[source][im] != std::numeric_limits<double>::max() &&
          m_conn[im][sink] != std::numeric_limits<double>::max() &&
          m_conn[source][sink] > m_conn[source][im] + m_conn[im][sink]){
           m_conn[source][sink] = m_conn[source][im] + m_conn[im][sink];
        }
      }
    }
  }
}

double WGraph::cheapestCost(VertexID i, VertexID j){
  return m_conn[i][j]; //constant
}

void WGraph::computeMST() {
  // Find Minimum Spanning Tree
}

void WGraph::printGraph() {
  for (int i = 0; i < m_size; i++) {
    for (int j = 0; j < m_size; j++) {
      cout << m_adj[i][j] << " ";
    }
    cout << endl;
  }
}