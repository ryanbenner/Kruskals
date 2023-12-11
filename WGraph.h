/*
1. Identifying Info:
    a. Ryan Benner
    b. 2394381
    c. rbenner@chapman.edu
    d. CPSC 350-01
    e. Assignment 6

    WGraph header file
*/

#ifndef WGRAPH_H
#define WGRAPH_H

#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include "PQueue.h"

using namespace std;

// a weighted, undirected WGraph implemented with adjacency matrix
// fixed size
typedef unsigned int VertexID;

struct Edge { // I chose to create a structure Edge because we needed to store several variable per edge,
// this allows you to track source/destination of each edge, as well as compare them by weight
		int source,destination;
		double weight;
		Edge() {
			source = 0;
			destination = 0;
			weight = std::numeric_limits<double>::max();
		}
		Edge(int src, int dst, double wgt) {
			source = src;
			destination = dst;
			weight = wgt;
		}

		bool operator<(const Edge& edge) const{
			return weight < edge.weight;
		}
		bool operator>(const Edge& edge) const{
			return weight > edge.weight;
		}

		friend std::ostream& operator << (std::ostream& o, const Edge& edge) {
			o << "Edge SRC: " << edge.source << "; Edge DST: " << edge.destination << "; Edge Weight: " << edge.weight;
		}
	};

class WGraph
{
public:
	WGraph();
	WGraph(unsigned int sz);
	~WGraph();
	void addEdge(VertexID i, VertexID j, double w);
	void removeEdge(VertexID i, VertexID j);
	bool areAdjacent(VertexID i, VertexID j);
	double cheapestCost(VertexID i, VertexID j);
	void calcFW();
	void printGraph(); // prints input graph
	void computeMST(); // computes and prints MST
	void printAllEdges(); // prints ALL edges from input file, in asc order
	int findRoot(int parent[], int i); // helper method

private:
	double **m_adj;		 // is there an edge between two vertices and what's the weight of the edge
	double **m_conn;	 // more general, is there a path between a start and a finish and what's the cost (all parts summed)
	unsigned int m_size; // nodes in WGraph (fixed)
	PQueue<Edge>* allEdges; // PQueue of Edge structures, by weight
	int findRoot(int parent[], int i); // helper method
};

#endif