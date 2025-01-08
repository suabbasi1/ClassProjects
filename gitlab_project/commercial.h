#ifndef COMMERCIAL_H
#define COMMERCIAL_H
#include <vector>
#include <utility>
using namespace std;
//Declares teh function for growing the commercial zones
class Commercial{
public:
    Commercial();
    void UpdateCom();
    void InitilizeCommercial();
    void GrowCommercial(int row,int col);
    int countAdjacentPopCommercial(int row, int col, int minPopulation);
    bool isAdjacentToPowerlineCommercial(int row, int col);
 
private:
    vector<pair<int, int> > commercialZones; //vector to store 2 int pairs
};

#endif