#include "Driver.h"
#include "WGraph.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    Driver dr(argv[1]);
    WGraph* graph = dr.getGraph();
    graph->printGraph(); 
    return 0;
}
