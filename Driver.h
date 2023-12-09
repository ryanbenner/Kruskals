#ifndef DRIVER_H
#define DRIVER_H
#include <sstream>
#include <fstream>
#include <iostream>
#include "WGraph.h"

using namespace std;

class Driver {
    public:
        Driver(const std::string& filename);
        ~Driver();
        void getFile(string input);
        void getMST();
        WGraph* getGraph();
    private:
        WGraph* graph;
};

#endif