#ifndef WGRAPH_H
#define WGRAPH_H

#include <iostream>
#include <limits>
#include <fstream>
#include <set>
#include <sstream>
#include "PQueue.h"

using namespace std;

// a weighted, undirected WGraph implemented with adjacency matrix
// fixed size
typedef unsigned int VertexID;

struct Edge {
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
	void printGraph();
	void computeMST();
	void printAllEdges();
	int findRoot(int parent[], int i);

	// struct Edge {
	// 	int source,destination;
	// 	double weight;
	// 	Edge(int src, int dst, double wgt) {
	// 		source = src;
	// 		destination = dst;
	// 		weight = wgt;
	// 	}

	// 	bool operator<(const Edge& edge) const{
	// 		return weight < edge.weight;
	// 	}
	// 	bool operator>(const Edge& edge) const{
	// 		return weight > edge.weight;
	// 	}

	// 	friend std::ostream& operator << (std::ostream& o, const Edge& edge) {
	// 		o << "Edge SRC: " << edge.source << "; Edge DST: " << edge.destination << "; Edge Weight: " << edge.weight;
	// 	}
	// };

private:
	double **m_adj;		 // is there an edge between two vertices and what's the weight of the edge
	double **m_conn;	 // more general, is there a path between a start and a finish and what's the cost (all parts summed)
	unsigned int m_size; // nodes in WGraph (fixed)
	PQueue<Edge>* allEdges;
	std::set<Edge> mst;
	std::set<int> vertex;
};

#endif