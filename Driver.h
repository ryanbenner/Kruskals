/*
1. Identifying Info:
    a. Ryan Benner
    b. 2394381
    c. rbenner@chapman.edu
    d. CPSC 350-01
    e. Assignment 6

    Driver class header file
*/

#ifndef DRIVER_H
#define DRIVER_H
#include <fstream>
#include <iostream>
#include "WGraph.h"

using namespace std;

class Driver
{
public:
    Driver(const std::string &filename);
    ~Driver();
    void getFile(string input);
    void getMST();
    WGraph *getGraph();

private:
    WGraph *graph;
};

#endif