/*
1. Identifying Info:
    a. Ryan Benner
    b. 2394381
    c. rbenner@chapman.edu
    d. CPSC 350-01
    e. Assignment 6

    Driver class implementation, processes input file and creates Graph
*/

#include "Driver.h"

Driver::Driver(const std::string &filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    int sz;
    inputFile >> sz;
    graph = new WGraph(sz);

    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            double weight;
            inputFile >> weight;
            graph->addEdge(i, j, weight);
        }
    }

    std::string end;
    inputFile >> end;
    if (end != "END")
    {
        std::cerr << "Invalid file format. Missing 'END.' marker." << std::endl;
        exit(EXIT_FAILURE);
    }
}

Driver::~Driver()
{
}

WGraph *Driver::getGraph()
{
    return graph;
}