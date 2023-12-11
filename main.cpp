/*
1. Identifying Info:
    a. Ryan Benner
    b. 2394381
    c. rbenner@chapman.edu
    d. CPSC 350-01
    e. Assignment 6

    main.cpp, takes input file,creates graph, computes MST
*/

#include "Driver.h"
#include "WGraph.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    Driver dr(argv[1]);
    WGraph *graph = dr.getGraph();
    graph->computeMST();
    return 0;
}
