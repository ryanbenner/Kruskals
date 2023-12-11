/*
1. Identifying Info:
    a. Ryan Benner
    b. 2394381
    c. rbenner@chapman.edu
    d. CPSC 350-01
    e. Assignment 6

    WGraph implementation from class, with required added methods
*/

#include "WGraph.h"
#include <iostream>
#include <iomanip>

using namespace std;

WGraph::WGraph()
{
  m_size = 0;
  m_adj = NULL;
  m_conn = NULL;
}

WGraph::WGraph(unsigned int sz)
{
  allEdges = new PQueue<Edge>(true);
  m_size = sz;
  // allocate sz * sz adj matrix
  m_adj = new double *[sz];
  m_conn = new double *[sz];
  for (int i = 0; i < m_size; ++i)
  {
    m_adj[i] = new double[sz];
    m_conn[i] = new double[sz];
  }
  // start with edges
  for (int i = 0; i < m_size; ++i)
  {
    for (int j = 0; j < m_size; ++j)
    {
      m_adj[i][j] = std::numeric_limits<double>::max(); // essentially infinity
      m_conn[i][j] = std::numeric_limits<double>::max();
    }
  }
}

WGraph::~WGraph()
{
  // release memory
}

void WGraph::addEdge(VertexID i, VertexID j, double w)
{
  if (i < m_size && j < m_size)
  {
    m_adj[i][j] = w;
    m_adj[j][i] = w;
    if (w > 0)
    {
      auto edge = Edge(i,j,w);
      allEdges->add(edge);
    }
  }
}

void WGraph::removeEdge(VertexID i, VertexID j)
{
  if (i < m_size && j < m_size)
  {
    m_adj[i][j] = std::numeric_limits<double>::max();
    m_adj[j][i] = std::numeric_limits<double>::max();
  }
}

bool WGraph::areAdjacent(VertexID i, VertexID j)
{
  return (m_adj[i][j] < std::numeric_limits<double>::max());
}

// Floyd - Worshol: Good for relatively stable graphs
void WGraph::calcFW()
{ // runtime complexity O(v^3)
  for (int i = 0; i < m_size; ++i)
  {
    for (int j = 0; j < m_size; ++j)
    {
      m_conn[i][j] = m_adj[i][j]; // start with conn == adj matrix
    }
  }
  for (int im = 0; im < m_size; ++im)
  { // intermediate points --> transitive closure
    for (int source = 0; source < m_size; ++source)
    { // source = starting point
      for (int sink = 0; sink < m_size; ++sink)
      { // sink = ending point
        if (source == sink)
        {
          continue;
        }
        else if (m_conn[source][im] != std::numeric_limits<double>::max() &&
                 m_conn[im][sink] != std::numeric_limits<double>::max() &&
                 m_conn[source][sink] > m_conn[source][im] + m_conn[im][sink])
        {
          m_conn[source][sink] = m_conn[source][im] + m_conn[im][sink];
        }
      }
    }
  }
}

double WGraph::cheapestCost(VertexID i, VertexID j)
{
  return m_conn[i][j]; // constant
}

void WGraph::computeMST()
{
  // Find Minimum Spanning Tree
  int parent[m_size];
  // Total Cost
  double totalMSTCost;

  // Initialize parent array
  for (int i = 0; i < m_size; ++i) {
    parent[i] = i;
  }

  double mstGraph[m_size][m_size];
  for (int i = 0; i < m_size; ++i) {
    for (int j = 0; j < m_size; ++j) {
      mstGraph[i][j] = std::numeric_limits<double>::max();  // Initialize to infinity
    }
  }

  // iterate over edges in ascending order of weight (pqueue)
  while (!allEdges->isEmpty()) {
    Edge minEdge = allEdges->remove();

    // find root of source and destination vertices
    int sourceRoot = findRoot(parent, minEdge.source);
    int destRoot = findRoot(parent, minEdge.destination);

    // if roots aren't the same, you can add the edge (checking to make sure it doesn't loop)
    if (sourceRoot != destRoot) {
      // Merge the components
      parent[sourceRoot] = destRoot;
      mstGraph[minEdge.source][minEdge.destination] = minEdge.weight;
      mstGraph[minEdge.destination][minEdge.source] = minEdge.weight;

      totalMSTCost += minEdge.weight;
    }
  }

  // print mst graph
  cout << "The MST Cost is: " << fixed << setprecision(1) << totalMSTCost << endl;
  for (int i = 0; i < m_size; ++i) {
    for (int j = 0; j < m_size; ++j) {
      if (mstGraph[i][j] != std::numeric_limits<double>::max()) {
        cout << fixed << setprecision(1) << mstGraph[i][j] << " ";
      } else {
        cout << "0.0 ";
      }
    }
    cout << endl;
  }
}

// Helper function to find the root of a component
int WGraph::findRoot(int parent[], int i) {
  while (parent[i] != i) {
    i = parent[i];
  }
  return i;
}

void WGraph::printGraph()
{
  for (int i = 0; i < m_size; i++)
  {
    for (int j = 0; j < m_size; j++)
    {
      cout << m_adj[i][j] << " ";
    }
    cout << endl;
  }
}

void WGraph::printAllEdges() {
  cout << "ALL EDGES:" << endl;
  for (int i = 0; i < allEdges->size(); i++) {
    cout << allEdges->get(i) << endl;
  }
}