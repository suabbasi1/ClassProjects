#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

extern vector<vector<int> > TreeRegion; //region layout just for the spread of trees

class Tree{
    public:
        Tree();
        void SpreadTree();
        void PrintTree();
        void NewIndustrialPopulation();

};
#endif
